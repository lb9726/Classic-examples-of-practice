/*
下面给定的程序是已经建立了一个带头结点的单项链表,链表中的各结点
按结点数据域中的数据递增有序连接函数fun的功能是:查找数据域中值为ch
的结点.找到后通过函数值返回该结点在链表中所处的顺序号;若不存在值为ch的
结点,函数返回0值
*/

#include<stdio.h>
#include<stdlib.h>
#define N 8
typedef struct list
{
	int data;
	struct list *next;
}SLIST;

int fun(SLIST *h,char ch)
{
	SLIST *p;
	int n = 0;
	p = h->next;
	while(p != NULL)
	{
		n++;
		if(p->data == ch)
			return n;
		else
		    p = p->next;
	}
	return 0;
}

SLIST *creatlist(char *a)
{
	SLIST *h,*p,*q;
	int i;
	h = p = (SLIST *)malloc(sizeof(SLIST));
	for(i = 0; i<N; i++)
	{
		q = (SLIST *)malloc(sizeof(SLIST));
		q->data = a[i];
		p->next = q;
		p = q;
	}
	p->next = 0;
	return h;
}

void outlist(SLIST *h)
{
	SLIST *p;
	p = h->next;
	if(p == NULL)
		printf("\nthe list is null!\n");
	else
	{
		printf("\nHead");
		do
		{
			printf("->%c",p->data);
			p = p->next;
		}while(p != NULL);
		printf("->End\n");
	}
}

int main()
{
	SLIST *head;
	int k;
	char ch;
	char a[N] = {'m','p','g','a','w','x','r','d'};
	head = creatlist(a);
	printf("\nThe list before inserting\n");
	outlist(head);
	printf("\nEnter a letter:");
	scanf("%c", &ch);
	k = fun(head, ch);
	if(k == 0)
		printf("\n Not found!\n");
	else
		printf("The sequence number is:%d\n",k);
	return 0;
}

















