#include "table.h"

int main()
{
	PERSONINFO person;
	FILE *file;
	int num=1;
	file=fopen("info.txt","wt");
	if(file==NULL)
	{
		printf("open file failed !\n");
		return 0;
	}
	while(num)
	{
		printf("姓名：");
		scanf("%s",person.name);
		printf("性别：");
		scanf("%s",person.sex);
		printf("职称：");
		scanf("%s",person.position);
		strcpy(person.grade,"1");
		fprintf(file,"%-6s %-6s %-6s %-6s\n",person.name,person.sex,person.position,person.grade);
		printf("是否继续！,1 ,0 : ");
		scanf("%d",&num);
	}
	fclose(file);
}

void readfile(char name[30])
{
	FILE *file;
	file= fopen(name,"rt");
	if(file == NULL)
	{
		printf("open %s failed !\n",name);
		return 0;
	}
	
	
}


/*
//保存员工信息
void SaveWorkerNode(WORKERS worker)						      //将职工信息保存到文件
{
	int n;
	NODE *p;
	FILE *fp;
	sort();												  //指向文件的指针
	printf("需要保存到文件吗?（1—保存，0—不保存）");
	scanf("%d",&n);
	if(n==1)
	{
		if(WorkerHead.next==NULL)
			printf("无");
		else 
			p=WorkerHead.next;
		if((fp = fopen("职工管理系统.txt", "wb+")) == NULL)    //打开文件，并判断打开是否正常
			printf("can not open file\n");					  // 打开文件出错
		while(p!=NULL)
		{
			fprintf(fp,"%-10s %-10d %-10s %-10d %-10d %-10s %-10.2f %10s\n",
					p->worker.Name,
					p->worker.Num,
					p->worker.Sex,
					p->worker.Age,
					p->worker.Rank,
					p->worker.Department,
					p->worker.Salary,
					p->worker.Passwd);
			p=p->next;
		}
		fclose(fp);
	printf("保存成功！！\n");								  //关闭文件
	}
	return;
}
*/

/*
//读取员工信息
void ReadWorkerNode(WORKERS worker)
{
	FILE *fp;												  //指向文件的指针
	if((fp = fopen("职工管理系统.txt", "rb")) == NULL)		  //打开文件
	{
		printf("can not open file\n");	  					  //不能打开
 		exit(0);
	}
	DestroyLinklist();
	//PRINTF1;
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
		AddWorkerNode(worker);                
	}
	fclose(fp);
	return ;
}
*/


