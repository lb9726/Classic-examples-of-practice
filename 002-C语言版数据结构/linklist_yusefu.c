#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

//链表节点
typedef struct node
{
	int data;
	struct node *next;
}node;


//创建环形链表
node *create(int n)
{
	node *p = NULL;
	node *head = NULL;
	head = (node *)malloc(sizeof(node));
	p = head;
	node *s = NULL;
	int i = 1;
	if( 0 != n)
	{
		while (i <= n)
		{
			s = (node *)malloc(sizeof(node));
			s->data = i++;
			p->next = s;  //将新生成的节点作为头节点的下一个
			p = s;
		}
		s->next = head->next;//最后生成的节点指向第一个节点释放头节点
	}
	free(head);//最后释放掉头节点
	head = NULL;
	return s->next;
}

int main()
{
	int n = 41;
	int m = 3;
	int i;
	node *p = create(n);
	node *temp;
	m %= n;    //m = m % n; 
	printf("m = %d\n",m);
	while (p != p->next)
	{
		for (i = 1; i < m-1; i++)//循环一次
		{
			p = p->next;//printf("p->next = %d\n",p->next->data);printf("p = %d\n",p->data);return 0;
		}
		printf("%d->",p->next->data);
		
		temp = p->next;
		p->next = temp->next;
		free(temp);
		temp = NULL;
		
		p = p->next;//
	}
	printf("%d\n",p->data);
	return 0;
}








