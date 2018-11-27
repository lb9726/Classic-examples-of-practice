#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define PORT 1234
#define MAXDATASIZE 100

void process(FILE *fp, int sockfd);
char * getMessage(char * sendline, int len, FILE *fp);

int main(int argc, char *argv[])
{
    int sockfd;
    struct hostent *he;
    struct sockaddr_in server;

    if (argc  != 2)
    {
        printf("Usage:%s <IP Address>\n", argv[0] );
        exit(1);
    }

    if (NULL == (he = gethostbyname(argv[1])))
    {
        printf("gethostbyname() error \n");
        exit(1);
    }

    if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        printf("Socket() error \n");
        exit(1);
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr);

    if (-1 == connect(sockfd, (struct sockaddr *)&server, sizeof(server)))
    {
        printf("connect () error \n");
        exit(1);
    }

    process(stdin, sockfd);
    close(sockfd);
}

void process(FILE *fp, int sockfd)
{
    char sendline[MAXDATASIZE], recvline[MAXDATASIZE];
    int num;
    printf("connect to server. \n");
    printf("Input client's name: ");
    if (NULL == fgets(sendline, MAXDATASIZE, fp))
    {
        printf("\n Eixt. \n");
        return ;
    }

    send(sockfd, sendline, strlen(sendline), 0);
    while (NULL != getMessage(sendline, MAXDATASIZE,fp))
    {
        send(sockfd, sendline, strlen(sendline), 0);
        if (0 == (num = recv(sockfd, recvline, MAXDATASIZE, 0)))
        {
            printf("Server terminated .\n");
            return ;
        }
        recvline[num] = '\0';
        printf("Server Message :%s\n", recvline );
    }
    printf("\n Eixt. \n");
}

char *getMessage(char *sendline, int len , FILE *fp)
{
    printf("Input string to server:");
    return (fgets(sendline, MAXDATASIZE, fp));
}