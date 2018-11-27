#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../include/account.h"


/******************************************
*函数名称：create_empty_account
*函数功能：创建一个账户空链表
*输入参数：void
*返回值  ：单链表头结点
*******************************************/
account create_empty_account(void)
{
	//为头结点动态申请内存空间
	account p = (account)malloc(sizeof(accountnode));
	p->next = NULL;

	return p;
}


/******************************************
*函数名称：print_accont
*函数功能：打印账户信息链表
*输入参数：单链表首地址
*返回值  ：void
*******************************************/
void print_account(account h)
{
	account p;

	while(h->next != NULL)
	{
		p = h->next;
		printf(" name:%s  ID:%s  fd:%d\n",p->DATA.onlinename,p->DATA.onlineID, p->DATA.onlinefd);
		h = h->next;
	}

	printf("\n");
}

/******************************************
*函数名称：clear_account
*函数功能：清空账户单链表
*输入参数：单链表首地址
*返回值  ：void
*******************************************/
void clear_account(account h)
{
	account p;

	while(h->next != NULL)
	{
		p = h->next;
		h->next = p->next;
		free(p);
	}
}

/******************************************
*函数名称：destroy_account
*函数功能：销毁账户单链表
*输入参数：单链表首地址
*返回值  ：void
*******************************************/
void destory_account(account h)
{
	account p;

	while(h->next != NULL)
	{
		p = h->next;
		h->next = p->next;

		free(p);

	}
	free(h);
}



/******************************************
*函数名称：insert_account
*函数功能：添加学生信息
*输入参数：单链表首地址， 学生数据
*返回值  ：-1：操作失败  0：操作成功
*******************************************/
int insert_account(account h, ACNT info)
{
	if(h == NULL)
		return -1;

	while(h->next !=NULL)
	{
		h = h->next;
	}

	account p = (account)malloc(sizeof(accountnode));
	strcpy(p->DATA.onlinename,info.onlinename);
	strcpy(p->DATA.onlineID,info.onlineID);
    p->DATA.onlinefd = info.onlinefd;


	p->next = h->next;  //p->next = NULL;
	h->next = p;		//h->next = p;

	return 0;
}

/*******************************************/
int is_empty_account(account h)
{
   //返回 1：空 0：非空
	return(h->next == NULL);
}
/*****************************************/

/******************************************
*函数名称：delete_account
*函数功能：按姓名删除结点
*输入参数：单链表首地址,  要删除的数据
*返回值  ：-1：操作失败  0：操作成功
*******************************************/


int delete_account(account h, int fd)
{
	if(is_empty_account(h))
	{
		return 0;
	}
	int flag = 0;
	while(h->next != NULL)
	{
		if(h->next->DATA.onlinefd==fd)
		{
			flag = 1;
			account p = h->next;
			h->next = p->next;
			free(p);
			break;
		}
		h = h->next;
	}

	return (flag?1:0);
}

/******************************************
*函数名称：locate_account
*函数功能：按姓名查找
*输入参数：单链表首地址， 待找的数据
*返回值  ：找到的结点
*******************************************/
account locate_account(account h, char *ID)
{
	account p = h;
	while(p->next != NULL && (strcmp(p->next->DATA.onlineID,ID)!=0))
		p = p->next;
	return p;
}



account locate_account1(account h, char *name)
{
	account p = h;
	while(p->next != NULL && (strcmp(p->next->DATA.onlinename,name)!=0))
		p = p->next;
	return p;
}















