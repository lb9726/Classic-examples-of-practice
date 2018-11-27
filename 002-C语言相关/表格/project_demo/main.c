#include "ui.h"

//boss登录          级别：-BOSS 2-经理，3-销售经理，4-兼职技术人员，5-兼职推销员
void boss()
{
	WORKERS worker;
	int iChoice = 0;
	while(1)
	{
		int ret = MainUI();
		switch(ret)
		{
			case 1: 
				do
				{
					AddWorkerUI();
					printf("需要继续添加吗？（0：不添加，1：继续）");
					scanf("%d",&iChoice);
				}while(iChoice);
				break;

			case 2:
				system("clear");
				printf("现有员工信息如下：\n");
				ShowWorkerinfoUI();
				printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
				break;

			case 3:
				do
				{	
					ChangeWorker(worker);
					printf("现有员工信息如下：\n");
					ShowWorkerinfoUI();
					printf("需要继续更改吗？（0：不更改，1：继续）");
					scanf("%d",&iChoice);		
				}while(iChoice);
				break;

			case 4:
				do
				{	
					DeleteWorker(worker);
					printf("\n删除成功！！\n");
					printf("现有员工信息如下：\n");
					ShowWorkerinfoUI();
					printf("需要继续删除吗？（0：不删除，1：继续）");
					scanf("%d",&iChoice);

				}while(iChoice);
				break;

			case 5: 
				ReadWorkerNode(worker);
				printf("读取成功！！\n");       
				printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
				break;

			case 6:
				SaveWorkerNode(worker);
				printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
				break;
				
			case 7:
				do
				{
					SeekWorkerNode(worker);
					printf("需要继续查找吗？（0：不查找，1：继续）");
					scanf("%d",&iChoice);
				}while(iChoice);
				break;
		}
		if( 0 == ret)
			break;
	}
	return;
}

//4-兼职技术人员，5-兼职推销员
void Jianzhiyuan()
{
	WORKERS worker;
	int iChoice = 0;
	while(1)
	{
		int ret = MainJZUI();
		switch(ret)
		{
			case 1:
				system("clear");
				ShowJZ();
				printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
				break;

			case 2:
				do
				{	
					system("clear");
					ChangeJZ();
					printf("需要继续更改吗？（0：不更改，1：继续）");
					scanf("%d",&iChoice);		
				}while(iChoice);
				break;

			case 3:
				SaveWorkerNode(worker);
				printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
				break;
		}
		if( 0 == ret)
			break;
	}
	return;
}	

//2-经理
void Manager()
{
	WORKERS worker;
	int iChoice = 0;
	while(1)
	{
		int ret = MainManagerUI();
		switch(ret)
		{
			case 1: 
				do
				{
					ManagerAddWorkerUI();
					printf("需要继续添加吗？（0：不添加，1：继续）");
					scanf("%d",&iChoice);
				}while(iChoice);
				break;

			case 2:
				system("clear");
				printf("现有员工信息如下：\n");
				ManagerShow(worker);
				printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
				break;

			case 3:
				do
				{	
					ManagerChangeWorker(worker);
					printf("现有员工信息如下：\n");
					ManagerShow(worker);
					printf("需要继续更改吗？（0：不更改，1：继续）");
					scanf("%d",&iChoice);		
				}while(iChoice);
				break;

			case 4:
				do
				{	
					ManagerDeleteWorker(worker);
					system("clear");
					printf("删除成功！！(请注意保存）\n\n");
					printf("现有员工信息如下：\n");
					ManagerShow(worker);
					printf("需要继续删除吗？（0：不删除，1：继续）");
					scanf("%d",&iChoice);
				}while(iChoice);
				break;

			case 5:
				SaveWorkerNode(worker);
				printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
				break;
		}
		if( 0 == ret)
			break;
	}
	return;
}

//3-销售经理
void XSManager()
{
	WORKERS worker;
	int iChoice = 0;
	while(1)
	{
		int ret = MainManagerUI();
		switch(ret)
		{
			case 1: 
				do
				{
					XSManagerAddWorkerUI();
					printf("需要继续添加吗？（0：不添加，1：继续）");
					scanf("%d",&iChoice);
				}while(iChoice);
				break;

			case 2:
				system("clear");
				printf("现有员工信息如下：\n");
				XSManagerShow(worker);
				printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
				break;

			case 3:
				do
				{	
					XSManagerChangeWorker(worker);
					printf("现有员工信息如下：\n");
					XSManagerShow(worker);
					printf("需要继续更改吗？（0：不更改，1：继续）");
					scanf("%d",&iChoice);		
				}while(iChoice);
	
				break;

			case 4:
				do
				{	
					XSManagerDeleteWorker(worker);
					system("clear");
					printf("删除成功！！(请注意保存）\n\n");
					printf("现有员工信息如下：\n");
					XSManagerShow(worker);
					printf("需要继续删除吗？（0：不删除，1：继续）");
					scanf("%d",&iChoice);
				}while(iChoice);
				break;

			case 5:
				SaveWorkerNode(worker);
				printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
				break;
		}
		if( 0 == ret)
			break;
	}
	return;
}

//Main()
int main(int argc,char *argv[])
{
	int rank;
	
	if(0==LoginUI())
		boss();
	else
	{
		printf("\n请输入您的级别:");               // 级别：-BOSS 2-经理，3-销售经理，4-兼职技术人员，5-兼职推销员
		scanf("%d",&rank);
		switch(CompareWorkerRank(rank))
		{
			case 2:
				Manager();
				break;
			case 3:
				XSManager();
				break;
			case 4:
				Jianzhiyuan();
				break;
			case 5:
				Jianzhiyuan();
				break;
		}
	}		
		
	return 0;
}






