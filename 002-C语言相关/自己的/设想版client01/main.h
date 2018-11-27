#ifndef _MAIN_H
#define _MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include<sys/shm.h>
#include<sys/stat.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

typedef struct _USER
{
	int iID; 				//用户编号 登录编号
	char szName[64]; 		//用户注册名 显示名称
	char szPass[40]; 		//用户密码
	char szip[20];   		//获取本机ip用于通讯
	char szipend[20];   	//存放上次登录的IP地址
	char szNote[30];   		//备注信息用于找回密码
	char timestart[20];  	//本次登录的开始时间 用于创建聊天文件
	char timeend[20];    	//存放上次登录的时间
	char timeregist[20];  	//存放注册的时间
}USER;

typedef struct _STNODE
{
	USER user;    
	struct _STNODE *next;
}STNODE;

#endif
