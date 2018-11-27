#ifndef DATA_CLIENT_H_INCLUDED
#define DATA_CLIENT_H_INCLUDED

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define MAXLINE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 8787
#define LEN 500
#define max(a,b) (a > b) ? a : b
#define OK 1
#define ERROR 0

#define NONE "\e[0m"
#define BLACK "\e[0;30m"
#define L_BLACK "\e[1;30m"
#define RED "\e[0;31m"
#define L_RED "\e[1;31m"
#define GREEN "\e[0;32m"
#define L_GREEN "\e[1;32m"
#define BROWN "\e[0;33m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[0;34m"
#define L_BLUE "\e[1;34m"
#define PURPLE "\e[0;35m"
#define L_PURPLE "\e[1;35m"
#define CYAN "\e[0;36m"
#define L_CYAN "\e[1;36m"
#define GRAY "\e[0;37m"
#define WHITE "\e[1;37m"
 
#define BOLD "\e[1m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define REVERSE "\e[7m"
#define HIDE "\e[8m"
#define CLEAR "\e[2J"
#define CLRLINE "\r\e[K" //or "\e[1K\r"


typedef int Status;
//注册客户的信息结构体
typedef struct reg_person_info
{
    int reg_num;        /*注册人员的编号，是唯一的*/
    char reg_name[40];  /*注册人员的昵称*/
    char reg_pwd[40];   /*注册人员的密码*/
}reg_person_info;

/*
typedef struct _MESSAGE
{	
	int  pnum;         //归属人编号
	int  num;          //编号
	char name[64];     //用户名
	char msg[LEN];     //登录时是密码，聊天时就是聊天内容
	char flag[30];     //操作标志
	int  state;        //在线状态
}MESSAGE;
*/

//操作信息结构体
typedef struct MESSAGE    
{
//    int  pnum;           //归属人编号
//    int  num;            //好友（其他人）编号
    char flag[50];
    char name[64];       //归属人姓名
    char msg[MAXLINE];   //发送消息的主体
//    char regtime[40];    //用户注册时间
//    int  state;         //在线状态
//    int  clientfd;
//    char IP[30];        
}MESSAGE;
#endif // DATA_CLIENT_H_INCLUDED














