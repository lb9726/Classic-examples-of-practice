#include "logic.h"

//添加员工信息 ---logic 层函数
int DealAddWorker(WORKERS worker)
{
	//过滤
	if( 20>worker.Age||worker.Age>45)
	{
		printf("\n添加失败！！(您添加的年龄要在20～45岁之间)\n\n");
		return -1;
	}
	if(strcmp(worker.Sex,"male") != 0 &&
	   strcmp(worker.Sex,"female") !=0)
	{
		printf("\n(性别要为 male female) 添加失败！！\n");
		return -2;
	}
	AddWorkerNode(worker);

	return 1;
}

//更改员工信息
void ChangeWorker(WORKERS worker)
{
	system("clear");
	ShowWorkerinfoUI();

	printf("需要更改的员工姓名：");
	scanf("%s",worker.Name);
	ChangeWorkerNode(worker);

	return;
}

//删除员工信息
void DeleteWorker(WORKERS worker)
{
	system("clear");
	ShowWorkerinfoUI();

	printf("需要删除的员工姓名：");
	scanf("%s",worker.Name);

	DeleteWorkerNode(worker);
	return;
}

//4-兼职技术人员，5-兼职推销员
//显示
void ShowJZ()
{
	int num;
	printf("请输入你的编号：");
	scanf("%d",&num);
	printf("您信息如下：\n");
	ShowJZData(num);
	return;
}

//更改
void ChangeJZ()
{
	int num;
	printf("请输入你的编号：");
	scanf("%d",&num);
	ChangeJZData(num);
	return;
}

//2-经理添加员工时过滤  rank = 4
int ManagerAddWorker(WORKERS worker)
{
	//过滤
	if(20>worker.Age||worker.Age>45)
	{
		printf("\n添加失败！！(您添加的年龄要在20～45岁之间)\n\n");
		return -1;
	}
	if(strcmp(worker.Sex,"male") != 0 &&
	   strcmp(worker.Sex,"female") !=0)
	{
		printf("\n(性别要为 male female) 添加失败！！\n");
		return -2;
	}
	if(worker.Rank !=4)
	{
		printf("\n添加失败！！\n");
		printf("您可以添加 级别 4-兼职技术人员的信息！！\n\n");
		return -3;
	}
	
	AddWorkerNode(worker);

	return 1;
}

//2-经理更改员工信息
void ManagerChangeWorker(WORKERS worker)
{
	system("clear");
	ManagerShow(worker);

	printf("需要更改的员工姓名：");
	scanf("%s",worker.Name);
	ChangeWorkerNode(worker);

	return;
}

//经理删除员工信息
void ManagerDeleteWorker(WORKERS worker)
{
	system("clear");
	ManagerShow(worker);
	printf("需要删除的员工姓名：");
	scanf("%s",worker.Name);

	DeleteWorkerNode(worker);
	return;
}

//3-销售经理添加员工时过滤  rank = 5
int XSManagerAddWorker(WORKERS worker)
{
	//过滤
	if(20>worker.Age||worker.Age>45)
	{
		printf("\n添加失败！！(您添加的年龄要在20～45岁之间)\n\n");
		return -1;
	}
	if(strcmp(worker.Sex,"male") != 0 &&
	   strcmp(worker.Sex,"female") !=0)
	{
		printf("(\n性别要为 male female) 添加失败！！\n");
		return -2;
	}
	if(worker.Rank !=5)
	{
		printf("\n添加失败！！\n");
		printf("您可以添加 级别 5-兼职推销员的信息！！\n\n");
		return -3;
	}
	
	AddWorkerNode(worker);

	return 1;
}

//3-销售经理更改员工信息
void XSManagerChangeWorker(WORKERS worker)
{
	system("clear");
	XSManagerShow(worker);

	printf("需要更改的员工姓名：");
	scanf("%s",worker.Name);
	ChangeWorkerNode(worker);

	return;
}

//经理删除员工信息
void XSManagerDeleteWorker(WORKERS worker)
{
	system("clear");
	XSManagerShow(worker);
	printf("需要删除的员工姓名：");
	scanf("%s",worker.Name);

	DeleteWorkerNode(worker);
	return;
}



