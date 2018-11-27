#include "ui.h"

int LoginUI()
{
    char user[40]={'\0'};
    char pass[40]={'\0'};
	int flag=1;
	WORKERS worker;
	//绘制界面
    system("clear");
    printf("\t小型公司职工管理系统\n\n\n");
	printf("\t用户名：");
	scanf("%s",user);
	printf("\t密  码：");
	scanf("%s",pass);

	if(strcmp(user,"admin") == 0 &&
	   strcmp(pass,"123") == 0)
	{
		flag=0;
		printf("\n欢迎%s进入...\n",user);
		printf("Press Any key to continue...\n");
    	while(getchar() == '\n');
		return flag;
	}
	else
	{
		ReadWorkerNode(worker);
		if(1==JudgeLogin(user,pass))
			return flag;
	}
}

//主界面BOSS
int MainUI()
{
    //i : int
	int iChoice = 0;

    system("clear");
	printf("========BOSS操作界面========\n\n");
    printf("\t1.添加员工信息\n");
    printf("\t2.显示员工信息\n");
	printf("\t3.更改员工信息\n");
	printf("\t4.删除员工信息\n");
	printf("\t5.读取员工信息\n");
	printf("\t6.保存员工信息\n");
	printf("\t7.查找员工信息\n");
    printf("\t0.退出\n");
	printf("\t-------------------\n");
	printf("\t请输入功能编号：");
    scanf("%d",&iChoice);
    
    return iChoice;
}

//界面 Manager
int MainManagerUI()
{
	int iChoice = 0;

    system("clear");
	printf("========经理、销售经理操作界面========\n\n");
    printf("\t1.添加员工信息\n");
    printf("\t2.显示员工信息\n");
	printf("\t3.更改员工信息\n");
	printf("\t4.删除员工信息\n");
	printf("\t5.保存员工信息\n");
    printf("\t0.退出\n");
	printf("\t-------------------\n");
	printf("\t请输入功能编号：");
    scanf("%d",&iChoice);
    
    return iChoice;
}

//界面 4-兼职技术人员，5-兼职推销员
int MainJZUI()
{
	int iChoice = 0;
	system("clear");
	printf("========职工个人操作界面========\n\n");
    printf("\t1.显示个人信息\n");
	printf("\t2.更改个人信息\n");
	printf("\t3.保存个人信息\n");
    printf("\t0.退出\n");
	printf("\t-------------------\n");
	printf("\t请输入功能编号：");
    scanf("%d",&iChoice);
    
    return iChoice;
}

//添加员工信息界面
void AddWorkerUI()
{
	system("clear");
	WORKERS worker;
	printf("====BOSS添加员工信息界面====\n\n");
	printf("输入员工姓名：");
	scanf("%s",worker.Name);
	printf("生成员工编号：%d\n",worker.Num=NumBuild());
	printf("输入员工性别：");
	scanf("%s",worker.Sex);
	printf("输入员工年龄：");
	scanf("%d",&worker.Age);
	printf("输入员工级别：");
	scanf("%d",&worker.Rank);
	printf("输入员工部门：");
	scanf("%s",worker.Department);
	printf("输入员工工资：");
	scanf("%f",&worker.Salary);
	strcpy(worker.Passwd,"123");

	DealAddWorker(worker);

	return ;
}

//显示员工信息界面
void ShowWorkerinfoUI()
{
	PRINTF1;
	CoverWorkerNode();
	return;
}

//经理添加员工信息界面
void ManagerAddWorkerUI()
{
	system("clear");
	WORKERS worker;
	printf("====经理添加员工信息界面====\n\n");
	printf("输入员工姓名：");
	scanf("%s",worker.Name);
	printf("生成员工编号：%d\n",worker.Num=NumBuild());
	printf("输入员工性别：");
	scanf("%s",worker.Sex);
	printf("输入员工年龄：");
	scanf("%d",&worker.Age);
	printf("输入员工级别：");
	scanf("%d",&worker.Rank);
	printf("输入员工部门：");
	scanf("%s",worker.Department);
	printf("输入员工工资：");
	scanf("%f",&worker.Salary);
	strcpy(worker.Passwd,"123");

	ManagerAddWorker(worker);

	return ;
}


//销售经理添加员工信息界面
void XSManagerAddWorkerUI()
{
	system("clear");
	WORKERS worker;
	printf("====销售经理添加员工信息界面====\n\n");
	printf("输入员工姓名：");
	scanf("%s",worker.Name);
	printf("生成员工编号：%d\n",worker.Num=NumBuild());
	printf("输入员工性别：");
	scanf("%s",worker.Sex);
	printf("输入员工年龄：");
	scanf("%d",&worker.Age);
	printf("输入员工级别：");
	scanf("%d",&worker.Rank);
	printf("输入员工部门：");
	scanf("%s",worker.Department);
	printf("输入员工工资：");
	scanf("%f",&worker.Salary);
	strcpy(worker.Passwd,"123");

	XSManagerAddWorker(worker);

	return ;
}










