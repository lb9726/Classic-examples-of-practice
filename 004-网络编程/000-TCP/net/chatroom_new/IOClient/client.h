#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<string.h>

#define PORT 1234
#define BACKLOG 5     // 设定listen 监听的最大连接数为5
#define MAXDATASIZE 1000
typedef struct
{
    int fd;
    char *name;
    struct sockaddr_in addr;
    char *data;
}CLINET;
#endif // CLIENT_H_INCLUDED
