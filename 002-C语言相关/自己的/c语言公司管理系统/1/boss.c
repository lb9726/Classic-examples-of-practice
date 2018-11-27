#include"ui.h"

//boss增删改查的操作的选项
//此函数在boss登录成功时调用
void BOSSaction(char name[30],char pos[30]) //再在登录成功时传一个职称的参数用来限制添加人员的职称和删除修改的人员的职称
{
	STNODE *head1=NULL;
	head1=readfiletolist("./personinfo.txt");//从文件中读取登录人员的信息
	int choice,choice1=1;
	char ch;
	while(choice1)
	{
		choice=BOSSMainUI(name);//bossUI层的返回操作选项的调用
		switch(choice)
		{
			case 1:
				head1=AdddicinfoUI(head1,pos);  //增加人员信息
				rethome();
				break;
			case 2:
				head1=deletedicinfo(head1,pos); //删除人员信息
				rethome();
				break;
			case 3:
				head1=Modifydicinfo(head1,pos); //修改人员信息
				rethome();
				break;
			case 4:
				searchnameorID(head1,pos);      //查找人员信息
				rethome();
				break;
			case 5:
				showdicinfo(head1,pos);          //显示人员信息
				rethome();
				break;
			case 6:                             //员工工资导入
				head1=bossinputsalary(head1);
				rethome();
				break;
			case 7:                              //查看工资报表
				bossshowtable(head1);                             
				rethome();
				break;
			case 8:                              //删除了的人员
				showdeleteinfo(pos);                           
				rethome();
				break;
			case 0:                             //退出保存操作
				confirmsave(head1);
				
		}
	}
}

/*****************************
功能:boss登录验证子函数
使用:在LoginUI中boss登录中调用
*****************************/
void bosslogin()
{
	char sname[20];
	char pass[30];
	int i = 1;
	for(i=1;i<4;i++)
	{
		printf("\t\033[46;31m***************boss登录***************************\033[0m\n");
		printf("\033[;31m 输入姓名:\033[0m");
		scanf("%s",sname);
		printf("\033[;31m 输入密码:\033[0m");
        getchar();
		hiden(pass);
		printf("\n");        
		if((strcmp(sname,"boss")==0)&&strcmp(pass,"123")==0)
		{
			if(iputchecking())//验证码输入为正确的
			{
				logininf(1,sname,pass);//用来写登录纪录和提示上次登录时间和次数
				BOSSaction(sname,sname);  //boss的操作函数
				break;
			}
		}
		else
			printf("\033[;31m用户名或密码错误!!\033[0m\n");
	}
	if(i==4)
	{
		printf("\033[;31m输入错误3次,自动退出系统!!\033[0m\n");
		exit(1);
	}
}

//boss录入工资
STNODE * bossinputsalary(STNODE *head)
{
	double zonge;
	STNODE *p=head->next;
	STNODE *p1=head->next;
	printf("\033[;31m请先录入销售总额:\033[0m");
	scanf("%lf",&zonge);
	while(p!=NULL)
	{
		p->person.zonge=zonge;
		p=p->next;
	}
	printf("\033[;31m销售总额录入成功!!!\n\033[0m");
	printf("\033[;31m正在进行一键录入工资操作,请稍后\033[0m");
	printdot();
	while(p1!=NULL)
	{
		judgesalary(p1);
//		printf("%d,%s,%.0lf,%.0lf,%.0lf,%s\n",p1->person.id,p1->person.name,p1->person.stasalary,p1->person.zonge,p1->person.salary,p1->person.beizhu);
		p1=p1->next;
	}
	printf("\033[;31m一键录入工资操作已完成,正在跳转操作界面,请稍后\033[0m");
	printdot();
//	bossshowtable(head);
	sleep(1);
	return head;
}

//boss查看工资报表
void bossshowtable(STNODE *head)
{
    system("clear");
	STNODE *p=head->next;
	
	printf("%-100s","----------------------------------------------------------------------------------------------------------------\n");
	printf("|\t\t\t\t\t\t**人员工资报表**\t\t\t\t\t       |\n");
	printf("%-100s","----------------------------------------------------------------------------------------------------------------\n");
	printf("%-9s%-13s%-15s%-15s%-18s%-16s%-50s","|编号|","|姓名  |", "|职    称 |","|固定工资|","|销 售 总 额|","|最终 工资|","|工    资    备     注     信     息       |\n");printf("%-100s","----------------------------------------------------------------------------------------------------------------\n");
	while(p!=NULL)
	
	{	printf("|%-4d| |%-8s|   | %-10s|  |%-8.0lf| |%-10.0lf | |%-9.0lf| |%-53s|\n",p->person.id,p->person.name,p->person.position,p->person.stasalary,p->person.zonge,p->person.salary,p->person.beizhu);
		p=p->next;
	}
	printf("%-100s","----------------------------------------------------------------------------------------------------------------\n");
}








