#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 1234
#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
    int sockfd;
    int num;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server;
    struct sockaddr_in peer;

    if (3 != argc)
    {
        printf("Usage: %s <IP Address> <message>\n", argv[0]);
        exit(1);
    }

    if (NULL == (he = gethostbyname(argv[1])))
    {
        printf("gethostbyname() error\n");
        exit(1);
    }

    if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        printf("socket() error \n");
        exit(1);
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr); // he->h_addr the first ip
    sendto(sockfd, argv[2], strlen(argv[2]), 0, (struct sockaddr *)&server, sizeof(server));

    socklen_t len;
    len = sizeof(server);

    while(1)
    {
        if (-1 == (num = recvfrom(sockfd, buf, MAXDATASIZE, 0, (struct sockaddr *)&peer, &len)))
        {
            printf("recvfrom() error \n");
            exit(1);
        }

        if (len != sizeof(server) || 0 != memcmp((const void *)&server, (const void *)&peer, len))
        {
            printf("Receive message from other server\n");
            continue;
        }
        buf[num] = '\0';
        printf("Server Message: %s.\n", buf);
        break;
    }
    close(sockfd);
}
