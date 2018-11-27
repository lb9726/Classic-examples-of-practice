#ifndef _DATA_H
#define _DATA_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*小字典结构体*/
typedef struct dictionary
{	
	int ID;
	char simpname[20];
	char wholename[100];
	char chinesename[100];	
}DIC;

typedef struct STNODE
{
	DIC diction;
	struct STNODE *next;
}STNODE;

static int choice1=0;

//读文件取出当前文件中最大的ID编号
int readfileID(STNODE *head);

//返回主界面函数
void rethome();

//打印信息函数
void print(DIC dic);

//等待键盘输入是一个数字1~2否则就一直等待用户输入
int inputdigit12(char ch);

//等待键盘输入是一个数字0~1否则就一直等待用户输入
int inputdigit01(char ch);


//销毁链表---砍头法
void DestroyLinklist(STNODE *head);

//保存函数
void save(STNODE *head);

//释放结点子函数
STNODE * DeleteNode(STNODE *head,STNODE *q);

//读文件到链表的子函数
STNODE * readfiletolist(char filename[30]);

//按缩写名查找并返回地址
STNODE *findname(STNODE *head,char suoxiename[30]);

//按编号查找并返回地址
STNODE *findID(STNODE *head,int bianhao);

//按名字或编号查找的函数
STNODE * findfordelete(STNODE *head);

//按名字或编号查找的函数
STNODE * findformodify(STNODE *head);

#endif









