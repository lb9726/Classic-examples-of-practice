/*
双向循环链表实践：要求实现用户输入一个数使得26个字母的排列发生变化，例如用户输入3
，输出结果 DEFGHIJKLMNOPQRSTUVWXYZABC
同时需要支持负数，例如：-3输出：XYZABCDEFGHIJKLMNOPQRSTUVW
*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define OK 1
#define ERROR 0

typedef char ElemType;
typedef int Status;

typedef struct DualNode
{
	ElemType data;
	struct DualNode *prior;
	struct DualNode *next;
}DualNode,*DuLinkList;


Status InitList(DuLinkList *L)
{
	DualNode *p,*q;
	int i;
	
	*L = (DuLinkList)malloc(sizeof(DualNode));
	if (! (*L))
	{
		return ERROR;
	}
	(*L)->next = (*L)->prior = NULL;
	p = (*L);
	
	for (i = 0; i < 26; i++)
	{
		q = (DualNode *)malloc(sizeof(DualNode));
		if( !q)
		{
			return ERROR;
		}
		q->data = 'A' + i;
		q->prior = p;
		q->next = p->next;
		p->next = q;
		
		p = q;
	}
	p->next = (*L)->next;
	(*L)->next->prior = p;
	
	return OK;
}

void Caesar(DuLinkList *L,int i)
{
	if (i > 0)
	{
		do
		{
			(*L) = (*L)->next;
		}while(--i);
	}
	
	if (i < 0)
	{
		do
		{
			(*L) = (*L)->next;
		}while(++i);
	}
}


int main()
{
	DuLinkList L;
	int i,n;
	
	InitList(&L);
	printf("请输入一个整数：");
	scanf("%d",&n);
	printf("\n");
	Caesar(&L,n);
	
	for (i = 0; i < 26; i++)
	{
		L = L->next;
		printf("%c",L->data);
	}
	printf("\n");
	return 0;
}










