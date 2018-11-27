#ifndef _MAIN_H
#define _MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <time.h>
#include <linux/types.h>
#include <net/if.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include<sys/shm.h>
#include<sys/stat.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>


typedef struct _CHAT
{
	int iID;   //用于记录存储的位置
	char timechat[20];//记录当前的时间
	char szName[64];  //本客户端登录者的姓名
	char *buf; //聊天的内容
}CHAT;


typedef struct _USER
{
	int iNum;  				//用于标识 单人聊天还是群聊  登录 注册 找回密码
	int iID; 				//用户编号 登录编号
	char szName[64]; 		//用户注册名 显示名称
	char szPass[40]; 		//用户密码
	char szip[20];   		//获取本机ip用于通讯
	char szipend[20];   	//存放上次登录的IP地址
	char szNote[30];   		//备注信息用于找回密码
	char timestart[30];  	//本次登录的开始时间 用于创建聊天文件
	char timeend[30];    	//存放上次登录的时间
	char timeregist[30];  	//存放注册的时间
	CHAT chat; 				//存放聊天内容的结构体
}USER;

typedef struct _STNODE
{
	USER user;    
	struct _STNODE *next;
}STNODE;

static char systime[30];

USER *CliSendto(USER *Cliuser);
USER *CliSend(USER *Cliuser);
int getlocalip(char* outip);
void systemtime();
#endif
