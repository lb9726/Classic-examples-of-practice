#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

int main()
{
	int *p,i = 0;
	p = (int *)malloc(sizeof(int));
	printf("p = %p *p = %d\n",p,*p);
	free(p);
	printf("p = %p *p = %d\n",p,*p);
	p++;
	printf("p = %p *p = %d\n",p,*p);
	p++;
	printf("p = %p *p = %d\n",p,*p);
	for (i =0 ;i < 20; i++)
	{
		p++;
		printf("p = %p *p = %d\n",p,*p);
	}
	p = NULL;
	printf("p = %p \n",p);
	//printf("p = %p *p = %d\n",p,*p); //段错误 (核心已转储)
	return 0;
}
