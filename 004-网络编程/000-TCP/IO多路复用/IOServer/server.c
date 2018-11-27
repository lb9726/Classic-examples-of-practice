#include "server.h"

server_context_st *s_srv_ctx = NULL;

/*
服务器初始化失败的话，释放分配的内存
*/
void server_uninit()
{
    if (s_srv_ctx) 
    {
        free(s_srv_ctx);
        s_srv_ctx = NULL;
    }
}

/*
为服务器初始化做准备
*/
int server_init()
{
    s_srv_ctx = (server_context_st *)malloc(sizeof(server_context_st));
    if (s_srv_ctx == NULL) 
    {
        return -1;
    }
    memset(s_srv_ctx, 0, sizeof(server_context_st));

    int i = 0;
    for (;i < SIZE; i++) //赋初始值为-1
    {
        s_srv_ctx->clifds[i] = -1;
    }
    return 0;
}

/*===========================================================================
 *服务器端，调用socket生成套接字描述符
 *bind 通过绑定的端口号来保证地址的唯一性，一般客户端不需要bind
 *listen函数将bind的sockfd设置为监听描述符，完成之后返回返回的fd为监听描述符
 * ==========================================================================*/
int create_server_proc(const char* ip,int port)
{
    int  fd;
    struct sockaddr_in servaddr;
    fd = socket(AF_INET, SOCK_STREAM,0);  //调用socket生成套接字描述符
//    int flags = fcntl(fd, F_GETFL, 0);
//    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    if (-1 == fd) 
    {
        fprintf(stderr, "create socket fail,erron:%d,reason:%s\n",
                errno, strerror(errno));
        return -1;
    }

    /*一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用。*/
    int reuse = 1;
    if (-1 == setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))) {
        return -1;
    }

    bzero(&servaddr,sizeof(servaddr));       /*将目标中指定数目的字节置为0。经常用此函数对套接字地址结构进行初始化*/
    servaddr.sin_family = AF_INET;           /*设置IPV4协议族*/
    inet_pton(AF_INET,ip,&servaddr.sin_addr);/*将ip的字符串形式的IP地址转换成网络字节序的二进制IP地址*/
    servaddr.sin_port = htons(port);

    if (-1 == bind(fd, (struct sockaddr*)&servaddr, sizeof(servaddr))) 
    {
        perror("bind error: ");
        return -1;
    }

    listen(fd, LISTENQ); /*监听最大的连接数为5*/

    return fd;
}

/*
    处理是否接受客户端的请求
*/
int accept_client_proc(int srvfd)
{
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);
    int clifd = -1;

    printf("accpet clint proc is called.\n");

ACCEPT:
    clifd = accept(srvfd,(struct sockaddr*)&cliaddr,&cliaddrlen);

    if (-1 == clifd) 
    {
        if (errno == EINTR) //如果是一个中断信号,重新accept
        {
            goto ACCEPT;
        } 
        else 
        {
            fprintf(stderr, "accept fail,error:%s\n", strerror(errno));
            return -1;
        }
    }
    fprintf(stdout, "accept a new client: %s:%d\n",
            inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);

    //将新的连接描述符添加到数组中
    int i = 0;
    for (i = 0; i < SIZE; i++) 
    {
        if (s_srv_ctx->clifds[i] < 0) 
        {
            s_srv_ctx->clifds[i] = clifd;
            s_srv_ctx->cli_cnt++;
            break;
        }
    }

    if (i == SIZE) 
    {
        fprintf(stderr,"too many clients.\n");
        return -1;
    }
    printf("end accept!\n");
}

/*
    向客户端发送信息
*/
int handle_client_msg(int fd, MESSAGE buf, Login_STNODE * head) 
{
    if (0 == strcmp(buf.flag, "注册"))
    {
        
        printf("recv buf flag is :%s\n", buf.flag);
        strcpy(buf.flag, "注册成功");
        write(fd, &buf,sizeof(buf));
        printf(" :%s\n", buf.name);
        printf(" :%s\n", buf.msg);
        printf("writefile start\n");
        write_register_table(buf);
        printf("writefile end\n");
    }
    else if (0 == strcmp(buf.flag, "登录"))
    {
        printf("in login cases, revf buf flag is %s\n", buf.flag);
        int pass_check = check_client_logic_request(head, buf);
        printf("pass_check = %d\n",pass_check);
        if (pass_check)
        {
            strcpy(buf.flag, "登录成功");
            write(fd, &buf, sizeof(buf));
        }
        else 
        {
            strcpy(buf.flag, "登录失败");
            write(fd, &buf,sizeof(buf));
        }
    }

    return 0;
}

/*
    接收客户端的信息
*/
void recv_client_msg(fd_set *readfds,Login_STNODE * head)
{
    int i = 0, n = 0;
    int clifd;
    MESSAGE message;
    memset(&message, 0,sizeof(message));
    for (i = 0;i <= s_srv_ctx->cli_cnt;i++) 
    {
        clifd = s_srv_ctx->clifds[i];
        if (clifd < 0) 
        {
            continue;
        }
        /*判断客户端套接字是否有数据*/
        if (FD_ISSET(clifd, readfds))
        {
            //接收客户端发送的信息
            n = read(clifd, &message, MAXLINE);
            if (n <= 0) 
            {
                /* n == 0表示读取完成，客户都关闭套接字*/
                FD_CLR(clifd, &s_srv_ctx->allfds); // 将clifd位设置为0
                close(clifd);                      // 关闭描述符
                s_srv_ctx->clifds[i] = -1;         // 将描述符设置为-1
                continue;                   
            }
            printf("hanle_client start\n");
            handle_client_msg(clifd, message, head);
        }
    }
}

void handle_client_proc(int srvfd, Login_STNODE *head)
{
    int  clifd = -1;
    int  retval = 0;
    fd_set *readfds = &s_srv_ctx->allfds;
//    struct timeval tv;
    int i = 0;

    while (1) {
        /*每次调用select前都要重新设置文件描述符和时间，因为事件发生后，文件描述符和时间都被内核修改啦*/
        FD_ZERO(readfds);
        /*添加监听套接字*/
        FD_SET(srvfd, readfds);
        s_srv_ctx->maxfd = srvfd;

//        tv.tv_sec = 30;
//        tv.tv_usec = 0;
        /*添加客户端套接字*/
        for (i = 0; i < s_srv_ctx->cli_cnt; i++) 
        {
            clifd = s_srv_ctx->clifds[i];
            /*去除无效的客户端句柄*/
            if (clifd != -1) 
            {
                FD_SET(clifd, readfds); //将一个给定的文件描述符加入集合之中
            }
            s_srv_ctx->maxfd = (clifd > s_srv_ctx->maxfd ? clifd : s_srv_ctx->maxfd);
        }
        printf("start select!\n");
        /*开始轮询接收处理服务端和客户端套接字*/
        retval = select(s_srv_ctx->maxfd + 1, readfds, NULL, NULL, NULL); // 如果是监听套接字就绪,说明有新的连接请求 
        if (-1 == retval) 
        {
            fprintf(stderr, "select error:%s.\n", strerror(errno));
            return;
        }
        if (0 == retval) 
        {
            fprintf(stdout, "select is timeout.\n");
            continue;
        }
        if (FD_ISSET(srvfd, readfds)) /*判断客户端套接字是否有数据*/
        {
            printf("*监听客户端请求*\n");
            accept_client_proc(srvfd);/*监听客户端请求*/
        } 
        else 
        {
            printf("*接受处理客户端消息*\n");
            recv_client_msg(readfds, head);/*接受处理客户端消息*/
        }
    }
}

int main(int argc,char *argv[])
{
    int srvfd;
    Login_STNODE *register_file_head;
//    register_file_head = NULL;
    /*初始化服务端context*/
    if (server_init() < 0) 
    {
        return -1;
    }
    /*创建服务,开始监听客户端请求*/
    srvfd = create_server_proc(IPADDR, PORT);
    if (srvfd < 0) 
    {
        fprintf(stderr, "socket create or bind fail.\n");
        goto err;
    }
    register_file_head = readfiletolist_for_login("./dat/register_info.txt");
    print_personinfo(register_file_head);
    /*开始接收并处理客户端请求*/
    handle_client_proc(srvfd, register_file_head);
    server_uninit();
    return 0;
err:
    server_uninit();
    return -1;
}












