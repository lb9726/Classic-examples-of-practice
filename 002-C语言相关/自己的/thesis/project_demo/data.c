#include "data.h"

//添加员工信息
int AddWorkerNode(WORKERS worker)
{
	NODE *p = malloc(sizeof(NODE));
	p->worker = worker;
	p->next = NULL;

	p->next = WorkerHead.next;
	WorkerHead.next = p;

	return 1;
}

//遍历员工信息
void CoverWorkerNode()
{
	NODE *p = WorkerHead.next;
	sort();
	while(p!=NULL)                       
	{
		printf("\t%-10s %-10d %-10s %-10d %-10d %-10s %-10.2f\n",
				p->worker.Name,
				p->worker.Num,
				p->worker.Sex,
				p->worker.Age,
				p->worker.Rank,
				p->worker.Department,
				p->worker.Salary);
		p = p->next;

	}
	printf("\n");

	return;
}

//排序
void sort()
{
	NODE *p = NULL;
	for( p = WorkerHead.next; p!= NULL; p = p->next)
	{
		NODE *q = NULL;
		for( q = p->next; q != NULL; q = q->next)
		{
			if(q->worker.Num > p->worker.Num)
			{
				WORKERS tmp = q->worker;
				q->worker = p->worker;
				p->worker = tmp;
			}
		}
	}
	return;
}

//编号生成
int NumBuild()
{
	WORKERS worker;
	NODE *p = &WorkerHead;
	ReadWorkerNode(worker);
	sort();
	if(p->next==NULL)
		return 1;
	else
		return p->next->worker.Num + 1;
}

//更改员工信息
void ChangeWorkerNode(WORKERS worker)
{
	int b=0;
	NODE *p = &WorkerHead;
	
	while(p->next!=NULL)
	{ 
		if(strcmp(worker.Name,p->next->worker.Name) == 0) 
			break; 
		p=p->next; 
	}
	
	printf(" =============================================\n");  
	printf(" ** 1-姓名 2-编号 3-年龄 4-级别 5-部门 6-工资**\n");
	printf(" =============================================\n"); 
	printf("请选择你要修改的信息编号:"); 
	scanf("%d",&b); 
	getchar(); 

	switch(b)
	{ 
		case 1: 
			printf("请输入新姓名(原姓名:%s):",p->next->worker.Name); 
			scanf("%s",p->next->worker.Name);
			printf("修改成功!\n");
			getchar();
			break; 
		case 2: 
			printf("请输入新编号(原编号:%d):",p->next->worker.Num); 
			scanf("%d",&p->next->worker.Num);
			printf("修改成功!\n");
			break; 
		case 3:
			printf("请输入新年龄(原年龄:%d):",p->next->worker.Age);
			scanf("%d",&p->next->worker.Age);
			printf("修改成功!\n");
			break;
		case 4:
			printf("请输入新级别(原级别:%d):",p->next->worker.Rank);
			scanf("%d",&p->next->worker.Rank);
			printf("修改成功!\n");
			break;
		case 5:
			printf("请输入新部门(原部门:%s):",p->next->worker.Department);
			scanf("%s",p->next->worker.Department);
			printf("修改成功!\n");
			break;
		case 6:
			printf("请输入新工资(原工资:%.2f):",p->next->worker.Salary);
			scanf("%f",&p->next->worker.Salary);
			printf("修改成功!\n");
			break;
	}
	return;
}

//删除员工信息
void DeleteWorkerNode(WORKERS worker)
{
	
	NODE *p = &WorkerHead;

	while(p->next!=NULL)
	{
		if(strcmp(worker.Name,p->next->worker.Name) == 0)
		{
			NODE *q = p->next;                               //保存 要删除节点的位置			
			p->next = p->next->next;                         //链接删除节点的前一个节点和后一个节点
			free(q);
			q = NULL;
			return;
		}
	p = p->next;
	}
	return;
}

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

//销毁链表(砍头法)
void DestroyLinklist()
{
     NODE *q=WorkerHead.next;
     while(q!=NULL)
     {
       WorkerHead.next=q->next;
       free(q);
       q=WorkerHead.next;
     } 
}

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
		/*printf("\t%-10s %-10d %-10s %-10d %-10d %-10s %-10.2f %10s\n",
				worker.Name,
				worker.Num,
				worker.Sex,
				worker.Age,
				worker.Rank,
				worker.Department,
				worker.Salary,
				worker.Passwd);*/    
		AddWorkerNode(worker);                
	}
	fclose(fp);
	return ;
}

//查找员工信息
void SeekWorkerNode(WORKERS worker)
{
	int b=0;
	NODE *p = &WorkerHead;
	
	printf(" ===================\n");
	printf(" ** 1-姓名  2-编号 **\n");
	printf(" ===================\n"); 
	printf("请选择你要查找的信息编号:"); 
	scanf("%d",&b); 
	getchar();

	switch(b)
	{
		case 1:
			printf("请输入员工姓名:"); 
			scanf("%s",worker.Name);
			PRINTF1;
			while(p->next!=NULL)
			{ 
				if(strcmp(worker.Name,p->next->worker.Name) == 0) 
					printf("\t%-10s %-10d %-10s %-10d %-10d %-10s %-10.2f\n",
							p->next->worker.Name,
							p->next->worker.Num,
							p->next->worker.Sex,
							p->next->worker.Age,
							p->next->worker.Rank,
							p->next->worker.Department,
							p->next->worker.Salary); 
				p=p->next; 
			}
			break;
		case 2:
			printf("请输入员工编号:"); 
			scanf("%d",&worker.Num);
			PRINTF1;
			while(p->next!=NULL)
			{ 
				if(worker.Num == p->next->worker.Num) 
					printf("\t%-10s %-10d %-10s %-10d %-10d %-10s %-10.2f\n",
							p->next->worker.Name,
							p->next->worker.Num,
							p->next->worker.Sex,
							p->next->worker.Age,
							p->next->worker.Rank,
							p->next->worker.Department,
							p->next->worker.Salary); 
				p=p->next; 
			}
			break;
	}
	return;
}

//用户名 密码 判定
int JudgeLogin(char user[40],char pass[40])
{
	NODE *p = &WorkerHead;
	while(p->next!= NULL)
	{	
		if( strcmp( user,p->next->worker.Name ) == 0 &&
			strcmp( pass,p->next->worker.Passwd ) == 0 )
		{
			printf("\n欢迎%s进入....\n",user);
			printf("Press Any key to continue...\n");
    		while(getchar() == '\n');
			return 1;
		}
		p = p->next;
	}
	exit(0);
}

//级别比较
int CompareWorkerRank(int rank)
{
	int b=0;
	
	NODE *p = &WorkerHead;   
	
	while(p->next!=NULL)
	{
		if(rank == p->next->worker.Rank)
		{
			b = p->next->worker.Rank; 
			break;
		} 
		p=p->next; 
	}
	return b;
}

//2-经理 操作
//显示 级别 4-兼职技术人员的信息
void ManagerShow(WORKERS worker)
{	
	NODE *p = &WorkerHead;
	PRINTF1;
	while(p->next!=NULL)
	{ 
		if(4 == p->next->worker.Rank) 
			printf("\t%-10s %-10d %-10s %-10d %-10d %-10s %-10.2f\n",
					p->next->worker.Name,
					p->next->worker.Num,
					p->next->worker.Sex,
					p->next->worker.Age,
					p->next->worker.Rank,
					p->next->worker.Department,
					p->next->worker.Salary); 
		p=p->next; 
	}
	return;
}

//3-销售经理 操作
//显示 级别 5-兼职推销员的信息
void XSManagerShow(WORKERS worker)
{	
	NODE *p = &WorkerHead;
	PRINTF1;
	while(p->next!=NULL)
	{ 
		if(5 == p->next->worker.Rank) 
			printf("\t%-10s %-10d %-10s %-10d %-10d %-10s %-10.2f\n",
					p->next->worker.Name,
					p->next->worker.Num,
					p->next->worker.Sex,
					p->next->worker.Age,
					p->next->worker.Rank,
					p->next->worker.Department,
					p->next->worker.Salary); 
		p=p->next; 
	}
	return;
}

//4-兼职技术人员，5-兼职推销员
//显示个人信息
void ShowJZData(int num)
{
	NODE *p = &WorkerHead;
	PRINTF1;
	while(p->next!=NULL)
	{ 
		if(num == p->next->worker.Num)
		{
			printf("\t%-10s %-10d %-10s %-10d %-10d %-10s %-10.2f\n",
					p->next->worker.Name,
					p->next->worker.Num,
					p->next->worker.Sex,
					p->next->worker.Age,
					p->next->worker.Rank,
					p->next->worker.Department,
					p->next->worker.Salary);
			break;
		} 
		p=p->next; 
	}
	return;
}

//更改个人信息
void ChangeJZData(int num)
{
	int b=0;
	NODE *p = &WorkerHead;
	
	while(p->next!=NULL)
	{ 
		if(num == p->next->worker.Num)
			break; 
		p=p->next; 
	}
	
	printf(" ========================\n");  
	printf(" ** 1-姓名 2-年龄 3-密码**\n");
	printf(" ========================\n"); 
	printf("请选择你要修改的信息编号:"); 
	scanf("%d",&b); 
	getchar(); 

	switch(b)
	{ 
		case 1: 
			printf("请输入新姓名(原姓名:%s):",p->next->worker.Name); 
			scanf("%s",p->next->worker.Name);
			printf("修改成功!\n");
			getchar();
			break; 
		case 2: 
			printf("请输入新年龄(原年龄:%d):",p->next->worker.Age); 
			scanf("%d",&p->next->worker.Age);
			printf("修改成功!\n");
			getchar();
			break; 
		case 3:
			printf("请输入新密码(原密码:%s):",p->next->worker.Passwd); 
			scanf("%s",p->next->worker.Passwd);
			printf("修改成功!\n");
			getchar();
			break; 
	}
	return;
}














