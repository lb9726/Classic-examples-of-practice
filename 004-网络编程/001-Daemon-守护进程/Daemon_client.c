#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h> // zero()
#define PORT 1234
#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
    int fd;
    int numbytes;
    char buf[MAXDATASIZE];
//    struct hosten *he;
    struct sockaddr_in server;

    if (2 != argc)
    {
        printf("Usage: %s <IP address>\n", argv[0]);
        exit(-1);
    }

//    if (NULL == (he = gethostbyname(argv[1])))
//    {
//        perror("gethostbyname error.");
//        exit(1);
//    }

    if (-1 == (fd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("Create socket failed.");
        exit(1);
    }

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
//    server.sin_addr = *((struct in_addr *)he->h_addr);
    inet_aton(argv[1], &(server.sin_addr));
    if (-1 == (connect(fd, (struct sockaddr*)&server, sizeof(struct sockaddr))))
    {
        perror("connect failed");
        exit(1);
    }

    if (-1 == (numbytes = recv(fd, buf, MAXDATASIZE, 0)))
    {
        perror("recv error.");
        exit(1);
    }
    buf[numbytes] = '\0';
    printf("Server message: %s\n", buf);
    close(fd);
}
