#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void print(char *name[],int n)
{
	int i;
	for(i = 0;i < 2*n;i++)
	{
		printf("%-12s",name[i]);
		if(i%(8)==7)
			printf("\n");
	}
}

void addblank(char *name[])
{
	char *p=name[0];
	//p=(char *)malloc(sizeof(char *));
//	strcpy(p,name[1]);
//	strcat(p,"  a");
	strcat(name[1],"  a");
//	printf("%s\n",p);
}

void freeof(char *name[],int n)
{	
	int i = 0;
	for(i=0;i<n;i++)
	{
		printf("name[%d]=%p\n",i,name[i]);
		free(name[i]);
		
	}
}

void main()
{
	int n = 8;
	char *name[2*n];
	int i=0;
	for(i=0;i<2*n;i++)
	{
		name[i]=(char *)malloc(sizeof(char *)*20);printf("name[%d]=%p\n",i,name[i]);
		if(i%8==7){
			strcpy(name[i],"Creat wall");printf("i=%d\n",i);}
		else 
			strcpy(name[i],"Basic");
	}
	
	addblank(name);
	print(name,n);//addblank(name);	
	freeof(name,n);
}
