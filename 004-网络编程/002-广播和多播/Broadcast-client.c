/*
客户端程序，它的作用是侦听某一个固定端口的数据报，接收到数据报后就返回。
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 255

int main(int argc, char **argv)
{
    struct sockaddr_in localaddr;
    int sockfd;
    int n;
    char msg[BUFLEN+1];
    if (2 != argc)
    {
        printf("usage:%s<port>\n", argv[0]);
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "socket creating error in tcli.c\n");
        exit(1);
    }

    memset(&localaddr, 0, sizeof(struct sockaddr_in));
    localaddr.sin_port = htons(atoi(argv[1]));
    localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int opt = SO_REUSEADDR;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(sockfd, (struct sockaddr*)&localaddr, sizeof(localaddr)) < 0)
    {
        fprintf(stderr, "bind error in tcli.c\n");
        exit(2);
    }

    while(1)
    {
        n = read(sockfd, msg, BUFLEN);
        if (-1 == n)
        {
            fprintf(stderr, "read error in tcli.c \n");
            exit(3);
        }
        else
        {
            msg[n] = 0;
            printf("%s\n", msg);
        }
    }
}

/*
 ./client 1234
*/
