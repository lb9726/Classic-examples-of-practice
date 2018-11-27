#include "signal.h"
#include "../include/chat.h"
#include "../include/account.h"

#define N 20;
#define __DEBUG__ 1
char msg[100]; //客户端和服务器的信息
//格式
//第一个字节 1：在线信息 0：离线信息
//第二个字节 1：私聊 0：群聊
//第3——8字节 收件人ID
//第9——14字节  发件人ID
//第15——22字节 信息发送时间
//第23字节之后 信息内容


char user[60] = {'\0'}; //账户信息
//格式
//第一字节  1：登入 0：注册
//第2——7字节 ID号
//第8——13字节 密码
//第14字节之后 昵称

//用于储存用户信息
struct client_user
{
    char ID[7];
    char pwd[7];
    char name[20];
};

char onlinename[100] = {'\0'}; //存储所有在线用户名单
char online_name[20]; //存储一个在线用户名

account online; //在线用户链表
account allclient;//所有用户链表

int sock_fd;  //监听套接字

void *process_client_connection (void *arg);//线程函数

static void signal_handler(int signo)//ctrl+c 信号处理函数
{
    if(signo == SIGINT)
    {
        printf("\n警告！服务器被强制关闭！\n");
        destory_account(online);
        destory_account(allclient);
        close(sock_fd);
    }
    exit(-1);
}

//用户注册
void regist(int newfd)
{
    
    FILE *fp, *fp1;//文件指针
    int i, flag = -1;
    struct client_user tmp_user;//临时用户结构体
    struct client_user tmp[100];//临时用户结构体数组。用于文件内容的读写
    bzero(user, 60);//将用户信息user清零
    bzero(&tmp_user, sizeof(struct client_user));//将用户结构体数组清零

    recv(newfd, user, 60, 0);//接受客户端发来的用户信息
    
    //以只读方式打开用户数据文件
    if((fp1 = fopen("user.dat", "r")) == NULL)
    {
        perror("login_open");
        exit(-1);
    }
    
    fseek(fp1, -9, 2);//将文件指针偏移到ID处，读出最后一个用户ID，用于服务器ID分配
    int n = fscanf(fp1, "\n%s %s", tmp[0].ID, tmp[0].pwd);//将文件内容写入数组中
    
    fclose(fp1);

    //分配用户ID
    int ID = 201400+atoi(tmp[0].ID) + 1;
    sprintf(tmp_user.ID, "%d", ID);

    //将用户ID填入user中
    for(i=0; i<6; i++)
        user[i+1] = tmp_user.ID[i];

    //获取用户密码
    for(i=0; i<6; i++)
        tmp_user.pwd[i] = user[i+7];

    //获取用户昵称
    i=0;
    while(user[i+13] != '\0')
    {
        tmp_user.name[i] = user[i+13];
        i++;
    }
    //以只读方式打开用户数据文件
    if((fp = fopen("user.dat", "r")) == NULL)
    {
        perror("login_open");
        exit(-1);
    }
    
    for(i=0; i<100; i++)
    {
        n = fscanf(fp, "%s %s %s\n", tmp[i].name, tmp[i].ID, tmp[i].pwd);//将文件内容写入数组中
    
        if(strcmp(tmp_user.name, tmp[i].name) == 0)//用户昵称以存在
        {
            user[0] = 0; //注册失败
            fclose(fp);
            goto lab0;
        }

        if(n <0)break;
    }

    //以追加方式打开文件
    if((fp = fopen("user.dat", "a")) == NULL)
    {
        perror("open");
        exit(-1);
    }
    
    if(fprintf(fp, "%s %s %s\n", tmp_user.name, tmp_user.ID, tmp_user.pwd) == -1)//保存注册用户的信息
    {
        perror("fprintf");
        user[0] = 0;//注册失败
    }
    else
        user[0] = 1; // 注册成功
    fclose(fp);

lab0:if(send(newfd, user, 60, 0) <0)//将处理好的用户信息发送给客户端
     {
         perror("lab0 send");
     }
}

//登入处理函数
void login(int newfd)
{
    FILE *fp;
    struct client_user tmp_user;
    struct client_user tmp[100];
    bzero(&tmp_user, sizeof(struct client_user));

    
    recv(newfd, user, 60, 0);

    //获取用户ID
    int i;
    for(i=0; i<6; i++)
        tmp_user.ID[i] = user[i+1];

    //获取用户密码
    for(i=0; i<6; i++)
        tmp_user.pwd[i] = user[i+7];
    
    if((fp = fopen("user.dat", "r")) == NULL)//只读方式打开文件
    {
        perror("login_open");
        exit(-1);
    }
    
    allclient = create_empty_account();  //创建所有用户信息链表
    for(i=0; i<100; i++)
    {
        int n = fscanf(fp, "%s %s %s\n", tmp[i].name, tmp[i].ID, tmp[i].pwd);//将文件内容写入数组中
        if(n <0)break;

        ACNT client_info;
        strcpy(client_info.onlinename, tmp[i].name);
        strcpy(client_info.onlineID, tmp[i].ID);
        client_info.onlinefd = 0;
        
        insert_account(allclient, client_info);//创建用户信息链表
    }
    rewind(fp); //重置文件指针为头
    
    for(i=0; i<100; i++)
    {
        int n = fscanf(fp, "%s %s %s\n", tmp[i].name, tmp[i].ID, tmp[i].pwd);//将文件内容写入数组中

        if((strcmp(tmp_user.ID, tmp[i].ID) == 0) && (strcmp(tmp_user.pwd, tmp[i].pwd)==0))//如果ID和密码正确
        {
            user[0] = 1; //登入成功
            int j=0;

            //创建在线用户链表
            
            while(tmp[i].name[j] != '\0')
            {
                user[j+13] = tmp[i].name[j];
                j++;
            }

            strcpy(tmp_user.name, tmp[i].name);
            strcat(onlinename, tmp_user.name);
            strcat(onlinename, " ");

            ACNT info;
            strcpy(info.onlinename, tmp_user.name);
            strcpy(info.onlineID, tmp_user.ID);
            info.onlinefd = newfd;
            insert_account(online, info);            //在线用户链表
            strcpy(online_name, info.onlinename);
            break;

        }
        else
            user[0] = 0;//登入失败
        if(n <0)break;

    }
    fclose(fp);

    if(send(newfd, user, 60, 0) < 0)//发送处理后的用户信息
    {
        perror("255 send");
    }


    
}



int main(int argc, char *argv[])
{
    system("clear");
//参数由命令行输入
    if(argc != 3)
    {
        printf("format: %s, <server_ip> <server_port>\n", argv[0]);
        exit(1);
    }

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

//注册ctrl+c信号函数
    if (signal (SIGINT, signal_handler) == SIG_ERR)
    {
        fprintf (stderr, "Cannot handle SIGINT!\n");
        exit (EXIT_FAILURE);
    }

    //建套接字
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0)
    {
        perror("socket");
        exit(1);
    }

    //端口重复利用
    int opt = 1;
    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    //bind
    if(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        exit(1);
    }  


    //listen
    listen(sock_fd, 20);



    socklen_t addrlen = sizeof(client_addr);
    int conn_fd;
    int i=0;

    online = create_empty_account();  //创建在线用户信息链表

    while(1)
    {
     
        if((conn_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &addrlen)) == -1)
        {
            perror("accept");
        }   
        else
        {
            printf("connection with %s %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        }

        pthread_t thread_ids[20];
        pthread_create (&thread_ids[i++], NULL, process_client_connection, (void *)conn_fd);         
    
    }

    return 0;

}

void *process_client_connection (void *arg)
{
    int key;//用于接受客户端的选择，无实际意义，职位同步接受
    int regist_flag; //注册成功标志
    int login_flag;//登入成功标志
	int conn_fd = (int)arg;//接受主线程参数
    char to_ID[7]={'\0'};//发给谁的ID
    char from_ID[7]={'\0'};//谁发来的ID

	while (1)
	{   
     //接收客户端的选择   
lab1:   if(recv(conn_fd, &key, sizeof(key), 0) <= 0)
        {
            perror("lab1 recv");
        }
        if(send(conn_fd, &key, sizeof(key), 0) <= 0)
        {
            perror("lab1 send");
        }


        if(2 == key)
        {
            regist(conn_fd);//有人注册
            regist_flag = user[0];
            bzero(user, 60);
        
            if(1 == regist_flag)goto lab2;
            else if (0 == regist_flag)goto lab1;//注册失败
        }
        else if(1 == key)
        {
lab2:               
            login(conn_fd);//有人登入
            login_flag = user[0];
            bzero(user, 60);


            if(1 == login_flag)
            {
                send(conn_fd, onlinename, 100, 0);


                print_account(online);


            }
            else if (0 == login_flag)goto lab2;//登入失败
        }

        break;
    }
    //接受服务端发送过来的用户信息链表
    //
    account p = allclient;
    char tmp_buf[26] = {'\0'};
    while(p->next != NULL)
    {

        int j=0;
        for(j=0; j<6; j++)
            tmp_buf[j] = p->next->DATA.onlineID[j];
        j=0;
        while(p->next->DATA.onlinename[j] != '\0')
        {
            tmp_buf[j+6] = p->next->DATA.onlinename[j];
            j++;
        }


        if(send(conn_fd, tmp_buf, 26, 0)<0)
        {
            perror("send 链表");
            exit(1);
        }

        p = p->next;
    }

    memset(tmp_buf, '#', 25);
    send(conn_fd, tmp_buf, 26, 0);

    char s[40];
    bzero(msg, 100);
    int i=0;
    for(i=0; i<22; i++)
    {
        msg[i]='#';
    }

//接受服务端发送过来的在线用户链表
//
    p = online;
    while(p->next != NULL)
    {

        if(p->next->DATA.onlinefd != conn_fd)
        {
            sprintf(s, "%s 上线了，您可以和他/她聊天咯！", online_name);
            strcat(msg, s);
            if(send(p->next->DATA.onlinefd, msg, 100, 0)< 0)
            {
                perror("send 链表");
                exit(1);
            }
            bzero(msg, 100);
            for(i=0; i<22; i++)
            {
                msg[i]='#';
            }

        }

        p = p->next;
    }
    
  //开始接受聊天消息  
    while(1)
    {
      
        //接受信息
        bzero(msg, 100);
        int nbytes = recv(conn_fd, msg, 100, 0);
        if(nbytes < 0)
        {
            perror("recv");
            exit(1);
        }
        
        i=0;
        for(i=0; i<6; i++)
        {
            to_ID[i] = msg[i+2];
        }

        //如果不是群消息，进行消息保存
        if(strncmp(to_ID, "******", 6) != 0)
        {
            FILE *fps;
            char tmp_from_name[20] = {'\0'};
            char tmp_to_name[20] = {'\0'};
            char tt[9] = {'\0'};
            char from_ID[7] = {'\0'};
            char tmp_information[80] = {'\0'};
            char tmp_msg[100] = {'\0'};
        
            //提取谁发的ID
            for(i=0; i<6; i++)
            {
                from_ID[i] = msg[i+8];
            }
            //提取消息
            i=22;
            bzero(tmp_information, 80);
            while(msg[i] != '\0')
            {
                tmp_information[i-22] = msg[i];
                i++;
            }
        
            bzero(tmp_from_name, 20);
            bzero(tmp_to_name, 20);
            //获取发件人昵称
            account p = locate_account(allclient, from_ID);
            strcpy(tmp_from_name, p->next->DATA.onlinename);

            p = locate_account(allclient, to_ID);
            strcpy(tmp_to_name, p->next->DATA.onlinename);

            //获取发送信息的时间点    
            for(i=0; i<8; i++)
                tt[i] = msg[i+14];

            sprintf(tmp_msg, "%s to %s %s : %s", tmp_from_name,tmp_to_name,tt, tmp_information);
            //将消息保存到文件
            
            if( (fps=fopen("chat_logs.txt","a")) == NULL )
            {
                perror("open file:");
            }
            if(fprintf(fps,"%s\n",tmp_msg) == -1)
            {
                perror("写入失败");
            }
            fclose(fps);
        }
        else//为群消息
        {
            FILE *fps;
            char tmp_from_name[20] = {'\0'};
            char tt[9] = {'\0'};
            char from_ID[7] = {'\0'};
            char tmp_information[80] = {'\0'};
            char tmp_msg[100] = {'\0'};
            if(msg[1] = -1)
            {
                for(i=0; i<6; i++)
                {
                    from_ID[i] = msg[i+8];
                }

                i=22;
                bzero(tmp_information, 80);
                while(msg[i] != '\0')
                {
                    tmp_information[i-22] = msg[i];
                    i++;
                }

                bzero(tmp_from_name, 20);
                account p = locate_account(allclient, from_ID);
                strcpy(tmp_from_name, p->next->DATA.onlinename);
                
                //获取发送信息的时间点    
                for(i=0; i<8; i++)
                    tt[i] = msg[i+14];

                sprintf(tmp_msg, "%s to %s %s : %s", tmp_from_name,"all",tt, tmp_information);


                if( (fps=fopen("chat_logs.txt","a")) == NULL )
                {
                    perror("open file:");
                }
                if(fprintf(fps,"%s\n",tmp_msg) == -1)
                {
                    perror("写入失败");
                }
            }
            fclose(fps);
        }
        
        
        if(msg[0] == 1 && msg[1] == 1)//私聊
        {
            i=0;
            for(i=0; i<6; i++)
            {
                to_ID[i] = msg[i+2];
            }
            p = locate_account(online, to_ID);
            send(p->next->DATA.onlinefd, msg, 100, 0);
        }
        else if(msg[1] == -1)//群聊
        {
            p = online;
            while(p->next != NULL)
            {


                if(p->next->DATA.onlinefd != conn_fd)
                {
                    if(send(p->next->DATA.onlinefd, msg, 100, 0)< 0)
                    {
                        perror("send 链表");
                        exit(1);
                    }
                }

                p = p->next;
            }
            if(msg[0] == 2)
            {
                delete_account(online, conn_fd);
                break;
            }

        }
        
    }  
    
	
	close (conn_fd);
	pthread_exit (NULL);
}
