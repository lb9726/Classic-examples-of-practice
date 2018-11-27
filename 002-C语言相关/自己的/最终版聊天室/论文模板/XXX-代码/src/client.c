#include "../include/chat.h"
#include "../include/interface.h"
#include "../include/account.h"

#define __DEBUG__ 1

//主界面处理
void client_main_interface(int sock_fd, char *username, char *ID);
//登入处理
void client_login(int sock_fd, char *username, char *ID);
//注册处理
void client_regist(int sock_fd, char *username, char *ID);

char msg[100]; //客户端和服务器的信息
char onlinename[100];    //在线用户
//格式
//第一个字节 1：在线信息 0：离线信息
//第二个字节 1：私聊 0：群聊
//第3——8字节 收件人ID
//第9——14字节  发件人ID
//第15——22字节 信息发送时间
//第23字节之后 信息内容
int main(int argc, char *argv[])
{
    char username[20] = {'\0'}; //用户昵称
    char buffer[100] = {'\0'};  //键盘输入缓存
    char fromwho[20] = {'\0'};  //发件人
    char towho[20] = {'\0'};    //收件人
    char user_ID[7] = {'\0'};   //用户ID
    char other_ID[7] = {'\0'};  //对方ID
    char tt[9] = {'\0'};        //信息发送时间
    char information[80]={'\0'}; //信息内容

    struct tm *ptm;           //系统时间结构提
    time_t ts;                
     account allclient = create_empty_account();

    //提示命令行参数输入服务器IP与端口号
    if(argc != 3)
    {
        printf("format: %s <server_ip> <server_port>", argv[0]);
        exit(0);
    }

    //建立连接套接字
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0); 

    //连接服务器端
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect");
        exit(1);
    }
    
    //主界面
    client_main_interface(sock_fd, username, user_ID);

    ACNT recv_info;
    int n;
    char tmp_buf[26] = {'\0'};
    char tmp_ID[7]={'\0'};
    char tmp_name[20]={'\0'};
    int j;
    while(n = recv(sock_fd, tmp_buf, 26, 0)>0)
    {

        if(strncmp(tmp_buf, "#########", 9) == 0)
            break;
        j=0;
        for(j=0; j<6; j++)
            tmp_ID[j] = tmp_buf[j];
        j=0;
        while(tmp_buf[j+6] != '\0')
        {
            tmp_name[j] = tmp_buf[j+6];
            j++;
        }

        strcpy(recv_info.onlineID, tmp_ID);
        strcpy(recv_info.onlinename, tmp_name);
        recv_info.onlinefd = 0;
        insert_account(allclient, recv_info);

    }
    if(n < 0)
    {
        perror("recv 111");
        exit(1);
    }

    //I/O多路复用
    fd_set read_fds;  
    FD_ZERO(&read_fds);
    FD_SET(sock_fd, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    int max_fd = sock_fd>STDIN_FILENO?sock_fd:STDIN_FILENO;
    
    while(1)
    {
           
        fd_set tmp_fds = read_fds;

        if(select(max_fd+1, &tmp_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(1);
        
        }


        if(FD_ISSET(sock_fd, &tmp_fds))//链接套接字就绪
        {
            //清空msg
            bzero(msg, 100);

             n = recv(sock_fd, msg, 100, 0);
            if(n > 0)
            {
                
                //获取发件人ID
                int i=0;
                for(i=0; i<6; i++)
                    other_ID[i] = msg[i+8];
                
                if(strncmp(other_ID, "######", 6) != 0)
                {

                    //获取发件人昵称
                    account p = locate_account(allclient, other_ID);
                    strcpy(username, p->next->DATA.onlinename);

                    //获取发送信息的时间点    
                    for(i=0; i<8; i++)
                        tt[i] = msg[i+14];
                }
                else
                {
                    i=0;
                    char tmp_nname[20]={'\0'};
                    while(msg[i+22] != ' ')
                    {
                        tmp_nname[i] = msg[i+22];
                        i++;
                    }
                    strcat(onlinename, tmp_nname);
                        
                }
                //获取信息内容
                i=22;
                bzero(information, 80);
                while(msg[i] != '\0')
                {
                    information[i-22] = msg[i];
                    i++;
                }
                
                if(strncmp(other_ID, "######", 6) != 0)
                {
                    //打印信息
                    printf("%s", username);
                    printf("(%s):", tt);
                }
                printf("%s\n", information);
            }
            else
            {
                if(n < 0)perror("recv");
                else
                {
                    printf("对不起服务器出问题了\n");
                    printf("我们正在拼命抢修中，很抱歉给您造成麻烦了!\n");
                }
                break;
            }   
        }
        

        if(FD_ISSET(STDIN_FILENO, &tmp_fds)) //标准输入就绪
        {
lab0:
            bzero(msg, 100); //清空msg
            scanf("%s", buffer);
            buffer[strlen(buffer)] = '\0';
          
            if(strncmp(buffer, ".quit", 5) == 0)
                goto lab10;
            //获取信息内容
            char *s = strchr(buffer, ':');
            if(s == NULL)   
            {
                printf("消息格式出错\n");
                printf("亲，看看上面的格式，请重新输入\n");
                goto lab0;
            }
            else
            {
                int i=0;
                bzero(information, 80);
                while(*s != '\0')
                {
                    information[i] = *(++s);
                    i++;
                }
            }
            
            //获取收件人昵称
            int i=0;
            bzero(towho, 20);
            while(buffer[i] != ':')
            {
                towho[i] = buffer[i];
                i++;
            }
            
            
            if(strncmp(towho, "all", 3) == 0)//对所有用户发送信息
            {
                msg[0] = 1;
                msg[1] = -1; //群聊
            }
            else
            { 
                msg[1] = 1; //私聊

                if(strstr(onlinename, towho) == NULL)//对方不在线，发送离线消息
                    msg[0] = -1;
                else
                    msg[0] = 1;  //发送在线消息

            }
            if(strncmp(towho, "all", 3) != 0)
            {
                account p = locate_account1(allclient, towho);
                if(p->next == NULL)
                {
                    printf("该用户没有上线！请重新输入在线用户名!\n");
                    goto lab0;
                }
                sprintf(other_ID, "%s", p->next->DATA.onlineID);
            }
            else
            {
                strcpy(other_ID,"******");
            }

            //获取系统时间
            ts = time(NULL);
            ptm = localtime(&ts);

            //格式化时间信息
            sprintf(tt, "%2d:%2d:%2d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

            //将发件人ID、收件人ID填入msg
            for(i=0; i<6; i++)
            {
                msg[i+2] = other_ID[i];
                msg[i+8] = user_ID[i];
            }
            
            //将信息发送的时间点填入msg
            for(i=0; i<8; i++)
            {
                msg[i+14] = tt[i];
            }

           
           //将信息内容填入msg  
            strcat(msg, information);
            if(msg[1] == -1)
                strcat(msg, "(群发消息！)");
            //将msg 发送给服务器
            int len = send(sock_fd, msg, 100, 0);
            if(len < 0)
            {
                perror("send");
                
            }

        }

    }
lab10:   
    msg[0] = 2;
    msg[1] = -1;
    strcpy(other_ID,"******");
    //获取系统时间
    ts = time(NULL);
    ptm = localtime(&ts);
    //格式化时间信息
    sprintf(tt, "%2d:%2d:%2d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

    //将发件人ID、收件人ID填入msg
    int i=0;
    for(i=0; i<6; i++)
    {
        msg[i+2] = other_ID[i];
        msg[i+8] = user_ID[i];
    }

    //将信息发送的时间点填入msg
    for(i=0; i<8; i++)
    {
        msg[i+14] = tt[i];
    }

    sprintf(information, "%s%s", username,"下线咯！\n");
    //将信息内容填入msg  
    strcat(msg, information);
    //将msg 发送给服务器
    int len = send(sock_fd, msg, 100, 0);
    if(len < 0)
    {
        perror("send");
    }
    destory_account(allclient);
    //关闭套接字
    close(sock_fd);
    return 0;

}


/***********************************************
 *函数名称：client_main_interface
 *函数功能：主界面的处理
 *函数参数：sock_fd:连接套接字
 *          username:用户昵称
 *          ID：用户ID
 *          onlinename:在线用户
 *返回值  ：无
 ***********************************************/
void client_main_interface(int sock_fd, char *username, char *ID)
{
    int key; //菜单序号选择
    char tmp[10];

    menu();  //主菜单显示

    while(1)
    {
        key = atoi(fgets(tmp, 10, stdin));
        if((1 != key) && (2 != key) && (3 != key))
        {
            printf("输入出错，请重新输入。。。\n");
            continue;
        }
        else
            break;
    }

    send(sock_fd, &key, sizeof(key), 0);  //发送选择给服务器

    if(recv(sock_fd, &key, sizeof(key), 0) <= 0) //接受服务器标志
    {
        perror("recv");
    }


    switch(key)
    {
        case 1:client_login(sock_fd, username, ID);break;
        case 2:client_regist(sock_fd, username, ID);break;
        case 3:exit(0);
    }
}

/***********************************************
 *函数名称：client_regist
 *函数功能：注册的处理
 *函数参数：sock_fd:连接套接字
 *          username:用户昵称
 *          ID：用户ID
 *          onlinename:在线用户
 *返回值  ：无
 ***********************************************/
void client_regist(int sock_fd, char *username, char *ID)
{

    char user[60] = {'\0'}; //账户信息
    //格式
    //第一字节  1：登入 0：注册
    //第2——7字节 ID号
    //第8——13字节 密码
    //第14字节之后 昵称
    
    char passwd[7] = {'\0'};
    registface(username, passwd);
    printf("\n\t正在注册，请稍等...\n");

    user[0] = 0;  //标志为0 注册
    
    //因为为注册，故该用户没用ID，将ID置为0
    int i=0;
    for(i=1; i<7; i++)
        user[i] = 0;
    
    //将注册用户密码填入user
    for(i=7; i<13; i++)
        user[i] = passwd[i-7];

    //将注册用户的昵称填入user
    i=13;
    while(username[i-13] != '\0')
    {
        user[i] = username[i-13];
        i++;
    }
    
    //将用户信息发送给服务器处理，其中user[0]是注册和登入的标志位
    send(sock_fd, user, 60, 0);

    
    //接受服务器处理好的用户信息，此时user[0]是成功与失败的标志位
    recv(sock_fd, user, 60, 0);

    //获取服务器分配的ID
    for(i=1; i<7; i++)
        ID[i-1] = user[i];
    
    if(user[0] == 1) //user[0]为1，表示注册成功
    {
        //注册成功提示界面
        regist_success(ID, username);
        
        // 注册成功后进入登入界面
        client_login(sock_fd, username, ID);
    }
    else if(user[0] == 0)
    {
        //注册失败界面
        regist_failure();
        
       //返回至主界面 
        client_main_interface(sock_fd, username, ID);
    }
    
}

/***********************************************
 *函数名称：client_login
 *函数功能：登入的处理
 *函数参数：sock_fd:连接套接字
 *          username:用户昵称
 *          ID：用户ID
 *          onlinename:在线用户
 *返回值  ：无
 ***********************************************/
void client_login(int sock_fd, char *username, char *ID)
{
    char user[60] = {'\0'}; //账户信息
    //格式
    //第一字节  1：登入 0：注册
    //第2——7字节 ID号
    //第8——13字节 密码
    //第14字节之后 昵称
    char passwd[7] = {'\0'};

    //登入界面
    //获得键盘输入的ID和密码
    loginface(ID, passwd);

    printf("\n\t\t\t正在登入，请稍等...\n");


    user[0] = 1;  // 登入标志
    
    //将用户ID填入user
    int i=0;
    for(i=1; i<7; i++)
        user[i] = ID[i-1];
    
    //将用户密码填入user
    for(i=7; i<13; i++)
        user[i] = passwd[i-7];

    //将user 信息发送给服务器处理,其中user[0] = 1表示登入
    send(sock_fd, user, 60, 0);

    //接受服务器处理后的user，其中user[0] 表示成功与否
    recv(sock_fd, user, 60, 0);

    if(user[0] == 1)
    {
        //登入成功
        //提取该登入成功ID的昵称
        i=13;
        while(user[i] != '\0')
        {
            username[i-13] = user[i];
            i++;
        }
        //从服务器获得在线用i户
        bzero(onlinename, 100);
        recv(sock_fd, onlinename, 100, 0);

        //进入聊天界面
        loginfaceshow(username, onlinename);
    }
    else if(user[0] == 0)
    {
        //登入失败
        login_failure();
        //返回登入界面
        client_login(sock_fd, username, ID);
    }

}


