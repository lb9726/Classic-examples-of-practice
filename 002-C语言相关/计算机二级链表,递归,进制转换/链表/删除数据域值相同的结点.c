/*
程序中已经建立了一个点头结点的单向链表,链表中的各个结点按数据域递增有序链接.
函数fun的功能是:删除链表中数据域值相同的结点,使之只保留一个.
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

//删除数据域相同的结点,只保留一个
void fun(SLIST *h)
{
	SLIST *p,*q;
	p=h->next;
	if(p!=NULL)
	{
		q=p->next;    //p是q的下一个结点,且p是头结点的下一个结点head->p->q->....->end
		while(q!=NULL)
		{
			if(p->data==q->data) //如果前一个地址的数据域与后一个结点的数据域相同则释放后一个结点的地址
			{
				p->next=q->next; //连接使得p的下一个是q的下一个,并且释放q
				free(q);
				q=p->next;//把q的下一个赋给了q ,相当于重新利用了q这个结点
			}
			else
			{
				p=q;         //如果p和q的数据不相同,则往后挪一位p=q q=q->next
				q=q->next;   //
			}
		}
	}
}

SLIST *creatlist(int *a)
{
	SLIST *h,*p,*q;
	int i;
	h=p=(SLIST *)malloc(sizeof(SLIST));
	for(i=0;i<N;i++)
	{
		q=(SLIST *)malloc(sizeof(SLIST));
		q->data=a[i];
		p->next=q;
		p=q;
	}
	p->next=0;
	return h;
}

void outlist(SLIST *h)
{
	SLIST *p;
	p=h->next;
	if(p==NULL)
		printf("\nthe list is null!\n");
	else
	{
		printf("\nHead");
		do
		{
			printf("->%d",p->data);
			p=p->next;
		}while(p!=NULL);
		printf("->End\n");
	}
}

int main()
{
	SLIST *head;
	int x;
	int a[N]={1,2,2,3,4,4,4,5};
	head=creatlist(a);
	printf("\nThe list before deleting:\n");
	outlist(head);
	fun(head);
	printf("\nThe list before deleting:\n");
	outlist(head);
	return 0;
}



