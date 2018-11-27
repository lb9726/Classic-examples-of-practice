#include"ui.h"

/***************************************
功能:skillperson修改查看的操作的选项
使用:此函数在skillperson登录成功时调用
传入参数:登陆成功者的姓名
***************************************/
void skillpersonaction(int id,char name[30])
{
	STNODE *head1=NULL;
	head1=readfiletolist("./personinfo.txt");//从文件中读取登录人员的信息
	int choice,choice1=1;
	while(choice1)
	{
		choice=skillpersonUI(name);//调用skillpersonUI层的返回值进行操作
		switch(choice)
		{
			case 1:
				showselfinfo(head1,id);
				rethome();
				break;
			case 2:
				head1=Modselfinfo(head1,id);
				rethome();
				break;
			case 0:
				confirmsave(head1);              //退出保存操作
				exit(0);
		}
    }
}


/***************************************
功能:skillperson登录验证的子函数
使用:登录时loginUI中的经理登录中调用
****************************************/
void skillpersonlogin(STNODE *head)//skillperson登录验证函数
{
	int i;
	char sname[20];
	char pass[30];
	for(i=1;i<4;i++)
	{
		printf("\t\033[46;31m****************技术人员登录**************************\033[0m\n");
		printf("\033[;31m输入姓名:\033[0m");
		scanf("%s",sname);
		printf("\033[;31m输入密码:\033[0m");
		getchar();
		hiden(pass);
		printf("\n");
		STNODE *p=head->next;  
		while(p!=NULL)
		{ 
			if((strcmp(sname,p->person.name)==0&&strcmp(pass,p->person.passwd)==0)&&strcmp("技术人员",p->person.position)==0)
			{     
				if(iputchecking())//验证码输入为正确的
				{
					logininf(p->person.id,p->person.name,p->person.passwd);
					skillpersonaction(p->person.id,p->person.name);//调用技术人员操作函数
					break;
				}
			}
		    p=p->next;
		}
		if(p==NULL)
			printf("\033[;31m用户名或密码错误!!\033[0m\n");
    }
    if(i==4)
    {
    	printf("\033[;31m输入错误3次,自动退出系统!!\033[0m\n");
    	exit(1);
    }
}








