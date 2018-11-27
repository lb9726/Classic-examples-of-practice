/*
程序中已经建立了一个带头结点的单向链表,在main函数中多次调用fun函数,每调用一次,输出链表尾部结点
中的数据,并释放该结点,使链表缩短
*/

#include<stdio.h>
#include<stdlib.h>
#define N 8
typedef struct list
{
	int data;
	struct list *next;
}SLIST;

void fun(SLIST *p)
{
	SLIST *t,*s;
	t = p->next;
	s = p;
	while(t->next != NULL)
	{
		s = t;
		t = t->next;
	}
	printf("%d", t->data);
	s->next = NULL;
	free(t);
}

SLIST *creatlist(int *a)
{
	SLIST *h,*p,*q;
	int i;
	h = p = (SLIST *)malloc(sizeof(SLIST));
	for(i = 0; i < N; i++)
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
			printf("->%d",p->data);
			p = p->next;
		}while(p != NULL);
		printf("->End\n");
	}
}

int main()
{
	SLIST *head;
	int x;
	int a[N] = {11,12,15,18,19,22,25,29};
	head = creatlist(a);
	printf("\n output from head:\n");
	outlist(head);
	printf("\noutput from tail:");
	while(head->next != NULL)
	{
		fun(head);
		printf("\n\n");
		printf("output from head again:\n");
		outlist(head);
	}
	return 0;
}



