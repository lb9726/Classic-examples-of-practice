
#include "CliUI.h"

//进入选择界面  101
int CliMainUI()
{
	int ichoice;
	printf("\t===============================\t\n");
	printf("\t=          1.用户登录         =\t\n");
	printf("\t=          2.用户注册         =\t\n");
	printf("\t=          3.找回密码         =\t\n");
	printf("\t=          4.退出             =\t\n");
	printf("请输入选择的编号：");
	scanf("%d",&ichoice);
	if(ichoice < 5 && ichoice > 0)
	{
		ichoice += 200;
		return ichoice;
	}
	printf("输入错误！\n返回本次开头！\n");
	return 101;
}

//进入用户登录界面  201
int CliLoginUI(USER *Cliuser)
{
	system("clear");
	printf("\t=====用户登录====\t\n");
	printf("\t=               =\t\n");
	printf("\t=    用户ID:");
	scanf("%d",&Cliuser->iID);
	printf("\t=    用户密码：");
	scanf("%s",Cliuser->szPass);
    printf("22222\n");	
	printf("Cliuser.iID = %d\n",Cliuser->iID);
	printf("Cliuser.iID = %s\n",Cliuser->szPass);
	CliSend(Cliuser);
	//将Cliuser 传到服务器端 进行验证  Clidata.c
	return 102;
}


//登录成功界面  102
int CliSeccesUI(USER *Cliuser)
{printf("Cliuser.iID = %d\n",Cliuser->iID);
	int ichoice;
	printf("\t===============================\t\n");
	printf("\t=          1.单人聊天         =\t\n");
	printf("\t=          2.群组聊天         =\t\n");
	printf("\t=          3.修改密码         =\t\n");
	printf("\t=          4.删除聊天记录     =\t\n");
	printf("\t=          5.上传下载文件     =\t\n");
	printf("\t=          6.退出登录         =\t\n");
	printf("请输入选择的编号：");
	scanf("%d",&ichoice);
	if(ichoice < 5 && ichoice > 0)
	{
		ichoice += 50;
		return ichoice;
	}
	printf("输入错误！\n返回本次开头！\n");
	return 102;
}

//单人聊天  51
int CliOneChatUI(USER *Cliuser)
{
	//1.显示当前好友
	//2.选择一个好友
	//3.调用聊天界面
	printf("单人聊天\n");
	return 102;
}
//聊天界面  单发
//退出单人聊天 回到102


//群组聊天  52
int CliGroupChatUI(USER *Cliuser)
{
	//1.查看当前群组
	//2.选择一个群组  
	//3.调用聊天界面
	printf("群组聊天\n");
	return 102;
}
//聊天界面 群发
//退出群组聊天  回到102


//修改密码   53
int CliChangePassUI(USER *Cliuser)
{
	//1.输入新密码
	//2.再次输入新密码
	//3.向服务器发送信息 修改密码
	//4.返回到  102
	printf("修改密码\n");
	return 102;
}

//删除聊天记录  54
int CliDelUI(USER *Cliuser)
{
	//1.显示  聊天记录
	//   只能操作服务器给自己建立的文件夹   文件夹名为ID号
	//2.选择某项删除  输入文件名删除
	//3.退出   102
}

//上传下载文件 
int CliUpDownUI()
{
	// 2个界面 一个上传 一个下载
	//1.上传  上传到群组文件夹中
	//2.下载  显示当前共享的文件名
	//下载到当前目录下
	//3.返回上个界面 102
}
//退出登录   56
int CliReturnUI()
{
	return 101;
}

//用户注册  202
int CliRegisterUI(USER *Cliuser)
{
	//1.输入用户名 密码 备注  自动获取时间
	
	printf("请输入用户名:");
	scanf("%s",Cliuser->szName);
	printf("请输入用户密码:");
	scanf("%s",Cliuser->szPass);
	//2.向服务器发送申请 写入服务器端的用户文件中
	//3.服务器返回一个生成的 ID
	printf("用户注册\n");
	CliSend(Cliuser);
	printf("Cliuser.iID = %d\n",Cliuser->iID);
	printf("Cliuser.iPass = %s\n",Cliuser->szPass);
	//5.做一个返回界面
	return 101;
}

//找回密码
int CliForgotUI(USER *Cliuser)
{
	//1.输入用户名 备注信息
	//2.将信息发送给服务器端  
	//3.服务器验证成功后返回 该用户密码
	printf("找回密码\n");
	return 101;
	//5.做一个返回界面
}



