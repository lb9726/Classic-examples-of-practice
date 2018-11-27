#ifndef DATA_SERVER_H
#define DATA_SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <error.h>
#include <sys/select.h>

#define PORT 1234
#define BACKLOG 5     // 设定listen 监听的最大连接数为5
#define MAXDATASIZE 1000
#define OK 1
#define ERROR 0
#define Maxfd 64
typedef  int  STATUS;

typedef struct message
{
    char flag[20];                          /*标志位*/ 
    char name[20];                      /*用户名*/  
    char msg[MAXDATASIZE];    /*消息内容*/
    char addrdest[20];                /*传输文件目的用户*/
    int size;                                   /*传输内容字节数*/
}msg_content;


#endif // DATA_SERVER_H
