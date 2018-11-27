/*
函数fun的功能是将bu带头结点的单项链表倒置,即若原链表中从头到尾结点
数据域依次为2,4,6,8,10,逆置后,从头到尾结点数据域依次为:10,8,6,4,2
*/

#include<stdio.h>
#include<stdlib.h>
#define N 5
typedef struct node
{
	int data;
	struct node *next;
}NODE;

NODE *fun(NODE *h)
{
	NODE *p,*q,*r;
	p = h;
	if(p == NULL)
		return NULL;
	q = p->next;
	p->next = NULL;
	while(q)
	{
		r = q->next;
		q->next = p;
		p = q;
		q = r;
	}
	return p;
}

NODE *creatlist(int a[])
{
	NODE *h,*p,*q;
	int i;
	h = NULL;
	for(i = 0; i<N; i++)
	{
		q = (NODE *)malloc(sizeof(NODE));
		q->data = a[i];
		q->next = NULL;
		if(h == NULL)
			h = p = q;
		else
		{
			p->next = q;
			p = q;
		}
	}
	return h;
}

void outlist(NODE *h)
{
	NODE *p;
	p = h;
	if(p == NULL)
	{
		printf("The list is NULL !\n");
	}
	else
	{
		printf("\nHead");
		do
		{
			printf("->%d",p->data);
			p = p->next;
		}while(p != NULL);
		printf("->End\n");
	}
}

int main()
{
	NODE *head;
	int a[N] = {2,4,6,8,10};
	head = creatlist(a);
	printf("\nThe original list:\n");
	outlist(head);
	head = fun(head);
	printf("\nThe list after inverting :\n");
	outlist(head);
	return 0;
}










