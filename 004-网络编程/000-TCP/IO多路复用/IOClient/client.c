#include "client.h"

void handle_recv_msg(int sockfd, MESSAGE buf) 
{
    printf("recv buf is :%s\n", buf.flag);
    strcpy(buf.flag,"注册成功");
    write(sockfd,&buf,sizeof(buf));
    
    if (0 == strcmp(buf.flag, "注册成功")) 
    {
        printf("client recv msg is:%s\n", buf.flag);
        ui_register(sockfd);
    }
}

void handle_connection(int sockfd)
{
    char sendline[MAXLINE],recvline[MAXLINE];
    MESSAGE message;
    //write(sockfd, &message, sizeof(message));
    int maxfdp,stdineof;
    fd_set readfds;
    int n;
//    struct timeval tv;
    int retval = 0;
    while (1) 
    {
        FD_ZERO(&readfds);
        FD_SET(sockfd,&readfds);
        maxfdp = sockfd;
printf("maxfdp = %d\n",maxfdp);
        //tv.tv_sec = 5;
        //tv.tv_usec = 0;
        retval = select(maxfdp + 1, &readfds, NULL, NULL, NULL);
        printf("retval = %d\n", retval);
        if (-1 == retval) 
        {
            return ;
        }

        if (0 == retval) 
        {
            printf("client timeout.\n");
            continue;
        }

        if (FD_ISSET(sockfd, &readfds)) 
        {
            ui_register(sockfd);
            n = read(sockfd,&message,MAXLINE);
            if (n <= 0) 
            {
                fprintf(stderr,"client: server is closed.\n");
                close(sockfd);
                FD_CLR(sockfd, &readfds);
                return;
            }
            handle_recv_msg(sockfd, message);
        }
        handle_recv_msg(sockfd, message);
    }
}

int main(int argc,char *argv[])
{
    int sockfd;
    MESSAGE message;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
//    int flags = fcntl(sockfd, F_GETFL, 0);
//   fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, IPADDRESS, &servaddr.sin_addr);

    int retval = 0;
    retval = connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if (retval < 0) 
    {
        fprintf(stderr, "connect fail,error:%s\n", strerror(errno));
        return -1;
    }
    printf("client send to server .\n");
    printf("sockfd = %d\n",sockfd);
    handle_connection(sockfd);
    return 0;
}











