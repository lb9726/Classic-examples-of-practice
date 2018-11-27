#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 1234
#define MAXDATASIZE 100

int main()
{
    int sockfd;
    struct sockaddr_in server;  // server's address information
    struct sockaddr_in client;  // client's address information
    socklen_t len;
    int num;
    char buf[MAXDATASIZE]; // buffer for message
    /*Creating UDP socket*/
    if ( -1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("Creating socket failed");
        exit(1);
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (-1 == (bind(sockfd, (struct sockaddr*)&server, sizeof(server))))
    {
        perror("Bind() error.");
        exit(1);
    }

    len = sizeof(client);

    while(1)
    {
        num = recvfrom(sockfd, buf, MAXDATASIZE, 0, (struct sockaddr *)&client, &len);
        if (num < 0)
        {
            perror("revform() error \n");
            exit(1);
        }
        buf[num] = '\0';
        printf("You got a message <%s> from client. \n It's Ip is %s, port is %d.\n",
            buf, inet_ntoa(client.sin_addr), htons(client.sin_port));
        sendto(sockfd, "welcome\n", 8, 0, (struct sockaddr *)&client, len);
        if (!strcmp(buf, "bye"))
        {
            break;
        }
    }
    close(sockfd);
}
