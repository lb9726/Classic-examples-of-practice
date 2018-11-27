/*应用程序只能通过UDP方式发生广播。一般情况下，如果调用sendto，
只能向非广播地址发送数据报。如果要发送广播数据报，必须告诉内核，
可以通过设置SO_BROADCAST套接口选项来做到这一点。
int on = 1;
setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(int));
以下是一个广播示例程序，它是一个服务器端程序，运行时需要指定广播地址和端口号，
运行后每3秒发送一次广播，将本机时间通知本子网的所有主机
*/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 255

void getcurtime(char *curtime)
{
    time_t tm;
    time(&tm);
    /*在curtime中放入当前时间的ASC表示*/
    snprintf(curtime, BUFLEN, "%s\n", ctime(&tm));
}

int main(int argc, char **argv)
{
    struct sockaddr_in peeraddr;
    int sockfd;
    int on = 1;
    char msg[BUFLEN+1];
    if (3 != argc)
    {
        printf("usage:%s<ip address><port>\n", argv[0]);
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "socket creating error in tserv.c\n");
        exit(1);
    }

    //setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(int)); // 设置广播方式
    memset(&peeraddr, 0, sizeof(struct sockaddr_in));
    peeraddr.sin_family = AF_INET;
    if (inet_pton(AF_INET, argv[1], &peeraddr.sin_addr) <= 0)
    {
        printf("Wrong dest IP address\n");
        exit(0);
    }
    peeraddr.sin_port = htons(atoi(argv[2]));
    for (; ;)
    {
        getcurtime(msg);
        int a;
        a = sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr*)&peeraddr, sizeof(peeraddr));
        printf("sendto bytes is %d\n", a);
        fflush(stdout);
        sleep(3);
    }
}

/*
 ifconfig
 Bcast:192.168.111.255
 ./server 192.168.111.255 1234
 
 服务器端的程序改动不大，只需要将广播工作方式去掉，发送地址指定为多播地址即可
*/








