/*
N名学生的成绩已经在主函数中放入一个带有头结点的链表结构中,
h指向链表的头结点.
*/

#include<stdio.h>
#include<stdlib.h>
#define N 8

struct slist
{
	double s;
	struct slist *next;
};

typedef struct slist STREC;

double fun(STREC *h)
{
	double max=h->s;
	while(h!=NULL)
	{
		if(max<h->s)
			max=h->s;
		h=h->next;
	}
	return max;
}

STREC *creat (double *s)
{
	STREC *h,*p,*q;
	int i=0;
	h=p=(STREC *)malloc(sizeof(STREC));
	p->s=0;
	while(i<N)
	{
		//产生8个结点的链表,各分数存入链表中
		q=(STREC *)malloc(sizeof(STREC));
		q->s=s[i];
		i++;
		p->next=q;
		p=q;  //不能少
	}
	p->next=NULL;
	return h;  //返回链表的首地址
}

outlist (STREC *h)
{
	printf("\n");
	STREC *p;
	p=h->next;
	printf("head");
	do
	{
		printf("->%2.0f",p->s);
		p=p->next;
	}while(p!=NULL);
	printf("\n");
}

void main()
{
	double s[N]={85,76,69,85,91,72,64,87},max;
	STREC *h;
	h=creat(s);
	outlist(h);
	max=fun(h);
	printf("max=%6.1f\n\n",max);
}











