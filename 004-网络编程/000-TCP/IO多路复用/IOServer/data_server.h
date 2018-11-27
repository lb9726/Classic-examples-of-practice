#ifndef DATA_SERVER_H
#define DATA_SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <fcntl.h>


#define IPADDR      "127.0.0.1"
#define PORT        8787
#define MAXLINE     1024
#define LISTENQ     5
#define SIZE        10
#define ISFALSE 0
#define ISTRUE 1
#define ERROR 0
#define OK 1
typedef int Status;
typedef struct server_context_st
{
    int cli_cnt;        /*客户端个数*/
    int clifds[SIZE];   /*客户端的个数*/
    fd_set allfds;      /*句柄集合*/
    int maxfd;          /*句柄最大值*/
} server_context_st;

//注册或登录的客户的信息结构体
typedef struct reg_person_info
{
    int reg_id;              /*注册人员的编号，是唯一的*/
    char reg_name[40];       /*注册人员的昵称*/
    char reg_pwd[40];        /*注册人员的密码*/
    char reg_time[50];       /*注册的时间*/
    int logincounts;         /*登录次数*/
    char lastlogintime[40];  /*上次登录的时间*/
}reg_person_info;

/*
//操作信息结构体
typedef struct MESSAGE    
{
    int  pnum;           //归属人编号
    int  num;            //好友（其他人）编号
    char name[64];       //归属人姓名
    char msg[MAXLINE];   //发送消息的主体
    char flag[50];
    char regtime[40];    //用户注册时间
    int  state;         //在线状态
    int  clientfd;
    char IP[30];        
}MESSAGE;
*/


//操作信息结构体
typedef struct MESSAGE    
{
    int  pnum;           //归属人编号
//    int  num;            //好友（其他人）编号
    char flag[50];
    char name[64];       //归属人姓名
    char msg[MAXLINE];   //发送消息的主体
//    char regtime[40];    //用户注册时间
//    int  state;         //在线状态
//    int  clientfd;
//    char IP[30];        
}MESSAGE;


/*
//登录信息
typedef struct logmes
{
	int id;                  //编号
	char name[30];           //登录人员的姓名
	char passwd[30];         //登录人员的密码
	int logincounts;         //登录次数
	char lastlogintime[40];  //上次登录的时间
}LOGMES;
*/

//登录人员信息结点
typedef struct Login_STNODE
{
    reg_person_info personinfo;
    struct Login_STNODE *next;
}Login_STNODE;

//文件判空函数
Status jugde_file_isEmpty(char filename[50]);

void generate_node_for_login(reg_person_info people,Login_STNODE *head);

void  read_login_table(char filename[],Login_STNODE *head);

void gettime(char *systime);

void write_register_table(MESSAGE message);

void judge_allocate(Login_STNODE *p);

void judge_openfile(char filename[], FILE *fp);

Login_STNODE * readfiletolist_for_login(char filename[30]);

void print_personinfo(Login_STNODE *head);
#endif // DATA_SERVER_H












