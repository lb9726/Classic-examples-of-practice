#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<strings.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<time.h>
#include<sys/file.h>

#define BUF_SIZE 1024

typedef struct _MESSAGE
{	
	int  pnum;         //归属人编号
	int  num;          //编号
	char name[64];     //用户名
	char msg[100];    //密码或聊天内容
	char flag[30];     //操作标志
	int  state;        //在线状态
}MESSAGE;

typedef struct _STHandle    
{
    MESSAGE message;
    struct _STHandle *next;
}STHandle;

static STHandle head;


int pnum0;             //保存登录者的帐号
char pname[64];        //保存登录者的用户名



int LoginUI(int sockfd);           //1.登录界面

int RegisterUI(int sockfd);        //2.注册界面

int RegAndLogUI(int sockfd);       //3.登录注册总界面

int GoodFriendUI(int sockfd);      //4.好友列表界面

int AddFriendUI();                 //5.添加好友界面

int DelFriendUI(int sockfd);       //6.删除好友界面

int ClientChatUI(int sockfd);      //7.0客户端聊天开始

int PrivateChatUI(int sockfd);     //7.聊天主界面

int ChatUI(int sockfd);            //8.私聊界面

int Record(int sockfd);            //9.聊天记录界面

int GroupChatUI(int sockfd);       //10.群聊界面

int Exit(int sockfd);              //11.退出界面

int MainUI(int sockfd);            //12.功能主界面

int gettime();                     //13，获取时间函数
