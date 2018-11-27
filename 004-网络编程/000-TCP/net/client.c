#include<stdio.h>
#include<strings.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netdb.h>

#define PORT  1234
#define MAXDATASIZE 100

int main(int argc, char const *argv[])
{
    int sockfd, num ;
    char buf[MAXDATASIZE] ;
    struct hostent *he ;
    struct sockaddr_in server ;

    if (argc != 2)
    {
        printf("Usage : %s < IP Address>\n", argv[0]) ;
        exit(1);
    }

    if ((he = gethostbyname(argv[1])) == NULL)
    {
        printf("gethostbyname() error !\n");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Socket() error \n");
        exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
//    server.sin_addr = *((struct in_addr *)he->h_addr);
    inet_aton(argv[1], &(server.sin_addr));
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        printf("connect () error \n");
        exit(1);
    }

    if ((num = recv(sockfd, buf ,MAXDATASIZE, 0)) == -1)
    {
        printf("recv() error \n");
        exit(1);
    }
    printf("%d\n", num );
    buf[num -1 ] = '\0';
    printf("sockfd = %d\n", sockfd);
    printf("server message: %s\n", buf);//printf("sockfd = %d\n", sockfd);
    close(sockfd);
    return 0;
}
