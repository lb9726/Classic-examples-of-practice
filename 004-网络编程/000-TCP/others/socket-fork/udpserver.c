#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 80
#define SERV_PORT 8888

void do_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
    int n;
    socklen_t len;
    char mesg[MAXLINE];

    for(;;)
    {
        len = clilen;
        /* waiting for receiving data */
        n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        /* sent data back to client */
        sendto(sockfd, mesg, n, 0, pcliaddr, len);
    }
}

int main(void)
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    //SOCK_DGRAM: Connectionless, unreliable datagrams of fixed maximum length.
    //IPPROTO_UDP = 17, User Datagram Protocol.
    //IPPROTO_IP = 0, Dummy protocol for TCP.
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); /* create a socket */

    /* init servaddr */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //Convert the host byte order to network byte order
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    /* bind address and port to socket */
    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("bind error");
        exit(1);
    }

    do_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

    return 0;
}

