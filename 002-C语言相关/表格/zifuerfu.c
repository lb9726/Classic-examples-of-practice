#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct _WORKERS
{
    char Name[64];       //姓名
	int Num;             //编号
    char Sex[48];        //性别 male female
	int  Age;            //年龄
    int Rank;            //级别  2 3 4 5
    char Department[48]; //部门
    float Salary;        //当月薪水
	char Passwd[40];     //密码
	float Ticheng;	     //提成    
}WORKERS;

void ReadWorkerNode();
void lines(char filename[30],int *a);

int  main()
{
	
	int a=0,b,i=0,j=0;
	lines("职工管理系统.txt",&a);
	ReadWorkerNode();
	char array[a][8];
/*	
	for(i=0;i<a*b;i++)
	{
		scanf("%s",ary);
	}
	for(i=0;i<a;i++)
	{
		for(j=0;j<b;j++)
		{
			printf("
		}
		printf("\n");
	}*/
	return 0;
}

void lines(char filename[30],int *a)
{
	FILE *fp;
	WORKERS worker;
	fp=fopen("职工管理系统.txt", "rb");
	if(fp == NULL)
	{printf("11221\n");
		printf("open file %s failed !\n",filename);
		return;
	}
	
	while(!feof(fp))
	{
		fscanf(fp, "%s %d %s %d %d %s %f %s\n",
				worker.Name,
				&worker.Num,
				worker.Sex,
				&worker.Age,
				&worker.Rank,
				worker.Department,
				&worker.Salary,
				worker.Passwd);//从文件读入记录   
		(*a)++;
	}
	printf("a=%d\n",*a);
	printf("\t%-7s %-7d %-7s %-7d %-7d %-7s %-7.2f\n",
							worker.Name,
							worker.Num,
							worker.Sex,
							worker.Age,
							worker.Rank,
							worker.Department,
							worker.Salary); 
	fclose(fp);
	fp=NULL;
	return;
}

//读取员工信息
void ReadWorkerNode()
{
	WORKERS worker;
	FILE *fp;												  //指向文件的指针
	if((fp = fopen("职工管理系统.txt", "rb")) == NULL)		  //打开文件
	{
		printf("can not open file\n");	  					  //不能打开
 		exit(0);
	}
	
	while(!feof(fp))
	{
		 
		fscanf(fp, "%s %d %s %d %d %s %f %s\n",
				worker.Name,
				&worker.Num,
				worker.Sex,
				&worker.Age,
				&worker.Rank,
				worker.Department,
				&worker.Salary,
				worker.Passwd);//从文件读入记录       
	}
	fclose(fp);
	return ;
}











