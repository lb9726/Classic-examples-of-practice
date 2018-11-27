#include"../include/interface.h"

#define __DEBUG__ 1
/****************************
*函数功能：客户主用户菜单
*函数名：menu()
*输入参数：无
*返回值：  无 
****************************/
void menu(void)
{	
		system("clear");
		printf(
					"\n\n\n\n\n\t\t********欢迎进入聊天系统*********"
					"\n\t\t1)---登录"
					"\n\t\t2)---注册"
					"\n\t\t3)---退出"
					"\n\t\t*********************************"
					"\n\t\t请输入选项："
				);

}


void press_enter()
{
	printf("\n\t\t请输入回车继续....");
    while(getchar() != '\n');
}

/**************************
*函数名：loginface()
*函数功能：登录函数
*输入参数：ID,pwd
*返回值：  无 
***************************/
void loginface(char *id, char *pwd)
{
    char *passwd;
	system("clear");
	printf(	"\n\t\t*************欢迎登录***************");
	printf("\n\t\t请输入用户ID：");
	scanf("%s",id);
	passwd = getpass("\n\t\t请输入密码：");
    int i;
    for(i=0; i<6; i++)
        pwd[i] = passwd[i];

	
}


/**************************
*函数名：loginfaceshow()
*函数功能：登录显示函数
*输入参数：
*返回值：  无 
***************************/
void loginfaceshow(char *username, char *onlinename)

{

	system("clear");
		printf(	"\n\t\t*************欢迎进入聊天系统***************"
				
				"\n\t\t登录用户：%s",username);
		printf("\n\n\t\t私聊格式为 在线用户：聊天内容 ");
		printf("\n\n\t\t群聊格式为 all：聊天内容 ");
		printf("\n\n\t\t退出:.quit ");
		printf("\n\n\t\t在线用户：%s\n",onlinename);
}


/**************************
*函数名：regist()
*函数功能：注册函数
*输入参数：name,pwd
*返回值：  无 
***************************/
void registface(char *name, char *pwd)
{
    char *passwd;
    system("clear");
	printf(	"\n\t\t*************欢迎注册***************");
	printf("\n\t\t请输昵称：");
	scanf("%s",name);
	passwd = getpass("\n\t\t请输入6位密码：");
    int i;
    for(i=0; i<6; i++)
        pwd[i] = passwd[i];
#if __DEBUG__
    printf("pwd = %s\n", pwd);
    printf("passwd = %s\n", passwd);
#endif
}


/**************************
*函数名：regist_success()
*函数功能：注册成功提示
*输入参数：name,id
*返回值：  无 
***************************/
void regist_success(char *id,char *name)
{
	system("clear");
	printf("\n\n\t\t*************注册成功***************");
	printf("\n\t\t您的ID：%s\n\n\t\t您的昵称：%s\n", id, name);
    while(getchar() != '\n');
	press_enter();
}

/**************************
*函数名：regist_failure()
*函数功能：注册失败函数
*输入参数：name,id
*返回值：  无 
***************************/
void regist_failure()
{
	system("clear");
	printf("\n\t\t*************注册失败***************");
    while(getchar() != '\n');
	press_enter();
}

/**************************
*函数名：login_failure()
*函数功能：登入失败函数
*输入参数：name,id
*返回值：  无 
***************************/
void login_failure()
{
	system("clear");
	printf("\n\t\t*************登入失败***************");
    while(getchar() != '\n');
	press_enter();
}

