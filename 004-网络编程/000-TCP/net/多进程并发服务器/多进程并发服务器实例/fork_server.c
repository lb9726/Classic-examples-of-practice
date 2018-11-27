#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 1234
#define BACKLOG 5
#define MAXDATASIZE 1000
void process_cli(int connfd, struct sockaddr_in client);

int main()
{
    int listenfd, connfd;
    pid_t pid;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int len;
    if (-1 == (listenfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("Creating socket falied.");
        exit(1);
    }

    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt));
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (-1 == (bind (listenfd, (struct sockaddr *)&server, sizeof(server))))
    {
        perror("Bind() error.");
        exit(1);
    }

    if (-1 == listen(listenfd, BACKLOG))
    {
        perror("listen() error \n");
        exit(1);
    }

    len = sizeof(client);

    while(1)
    {
        if (-1 == (connfd = accept(listenfd, (struct sockaddr *)&client, &len )))
        {
            perror("accept() error \n");
            exit(1);
        }

        if ((pid = fork()) > 0)
        {
            close(connfd);
            continue;
        }
        else if (pid == 0)
        {
            close(listenfd);
            process_cli(connfd, client);
            exit(0);
        }
        else 
        {
            printf("fork() error \n");
            exit(0);
        }
    }
    close(listenfd);
}

void process_cli(int connfd, struct sockaddr_in client)
{
    int num;
    char recvbuf[MAXDATASIZE], sendbuf[MAXDATASIZE], cli_name[MAXDATASIZE];
    printf("You got a connection from %s.", inet_ntoa(client.sin_addr) );
    num = recv(connfd, cli_name, MAXDATASIZE, 0);
    if (0 == num)
    {
        close(connfd);
        printf("client discconnected. \n");
        return;
    }

    cli_name[num - 1] = '\0';
    printf("client's name is %s.\n", cli_name );

    while (num = recv(connfd, recvbuf, MAXDATASIZE, 0))
    {
        recvbuf[num] = '\0';
        printf("Received client (%s) message:%s\n",  cli_name, recvbuf);
        int i = 0;
        for (i = 0 ; i < num - 1; i++)
        {
            if (recvbuf[i] >= 'a' && recvbuf[i] <= 'z' || recvbuf[i] > 'z')
            {
                recvbuf[i] = recvbuf[i] - 26;
            }
            sendbuf[i] = recvbuf[i];
        }
        sendbuf[num - 1] = '\0';
        send(connfd, sendbuf, strlen(sendbuf), 0);
    }
    close(connfd);
}