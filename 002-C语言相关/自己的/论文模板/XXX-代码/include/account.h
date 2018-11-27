#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

typedef struct acnt 
{

	char onlinename[20];
    char onlineID[7];
	int onlinefd;
}ACNT;

typedef struct ac_node
{
	ACNT DATA;
	struct ac_node *next;
}accountnode,*account;

//创建一个账户信息单链表
account create_empty_account(void);

void print_account(account h);

//清空
void clear_account(account h);
//销毁
void destory_account(account h);

//添加账户信息
int insert_account(account h, ACNT info);
int is_empty_account(account h);

//删除账户
int delete_account(account h, int fd);


//查找账户
account locate_account(account h, char *ID);

account locate_account1(account h, char *name);

#endif
