/*
从多播的原理可以看出，要接收多播数据报需要经过如下步骤：
1. 加入一个多播组。
2. 在指定的端口上进行侦听
3. 接收并处理到达的多播数据报
4. 离开多播组
5. 关闭句柄

下面，将接收广播时间的例子加以改造，使之接收多播分组，如下所示：
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
    struct ip_mreq mcaddr;
    if (3 > argc)
    {
        printf("usage:%s<multicast><port>\n", argv[0]);
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "socket creating error in tcli.c\n");
        exit(1);
    }

    memset(&localaddr, 0, sizeof(struct sockaddr_in));
    localaddr.sin_port = htons(atoi(argv[2]));
    localaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (inet_pton(AF_INET, "222.18.113.171", &mcaddr.imr_interface) <= 0)
    {/*置本地IP地址*/
        perror("failure:");
        exit(0);
    }
    /*加入哪个多播组由命令行参数给出*/
    if (inet_pton(AF_INET, argv[1], &mcaddr.imr_multiaddr) <= 0)
    {
        printf("Wrong multicast IP address\n");
        exit(0);
    }
    printf("ip: %s", inet_ntoa(mcaddr.imr_multiaddr));
    fflush(stdout);

    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcaddr, sizeof(mcaddr)) < 0)
    {
        /*加入多播组*/
        perror("setsockopt error in mtcli.c, join multicast failed\n");
        exit(4);
    }

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
