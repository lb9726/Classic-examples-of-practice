#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<time.h>

typedef struct linklist
{
	int data;
	struct linklist *next;
}STNODE;

STNODE * auto_generate_num( int n)
{
	int i;
	STNODE *head = (STNODE *)malloc(sizeof(STNODE));
	srand(time(NULL));
	for(i= 0; i < n ; i++)
	{
		STNODE *temp = head;
		STNODE *p = (STNODE *)malloc(sizeof(STNODE));
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = p;
		p->data = rand()%100;
		p->next = NULL;
	}
	return head;
}

void printnode(STNODE *head)
{
	STNODE *p = head->next;
	while(p != NULL)
	{
		printf("%-4d",p->data);
		p = p->next;
	}
	printf("\n");
	return ;
}

STNODE * return_address( STNODE *head,int num)
{
	
	STNODE *p = head->next;
	
	while(p != NULL)
	{
		if(p->data == num)
		{
			return p;
		}
		else
			p = p->next;
	}
	return NULL;
}

void DeleteNode(STNODE *head,STNODE *temp)
{
	STNODE *s = head;
	STNODE *t = s->next;
	while( t != NULL)
	{
		if(t == temp)
		{
			s->next = t->next;
			free(t);
			t = NULL;
			return ;
		}
		else
		{
			s = t;
			t = s->next;
		}
	}
}


int main()
{
	STNODE *head = NULL;
	STNODE *s = NULL;
	int n = 10;
	int id;
	head = auto_generate_num(n);
	printf("head = %p\n",head);
	while(1)
	{
		printnode(head);
		printf("请输入你想删除的数:");
		scanf("%d",&id);
		if(id == -1)
		{
			printf("停止删除！\n");
			break;
		}
		s = return_address(head,id);
		DeleteNode(head,s);
	}
	return 0;
}
