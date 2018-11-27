
#include "CliUI.h"

int main(int argc,char *argv[])
{
	USER Cliuser; //用于接收登录的 或 注册的 或 找回密码的 信息
	int iChoice = 101;
	while(iChoice)
	{
		switch(iChoice)
		{
		case 101:
			memset((char*)&Cliuser,0,sizeof(USER));//清空数据防止干扰
			iChoice = CliMainUI(); //进入选择界面
			//1.用户登录 2.用户注册 3.找回密码 4.退出
			break;
		case 201:
			iChoice = CliLoginUI(&Cliuser);  //进入用户登录界面
			break;
		case 102:
			iChoice = CliSeccesUI(&Cliuser); //登录成功界面
			//1.单人聊天 2.群组聊天 3.修改密码 4.返回上一界面
			break;
		case 51:
			iChoice = CliOneChatUI(&Cliuser); //单人聊天
			break;
		case 52:
			iChoice = CliGroupChatUI(&Cliuser); //群组聊天
			break;
		case 53:
			iChoice = CliChangePassUI(&Cliuser); //修改密码
			break;
		case 54:
			iChoice = CliDelUI(&Cliuser); //删除聊天记录
			break;
		case 55:
			iChoice = CliUpDownUI(&Cliuser);
			break;
		case 56:
			iChoice = CliReturnUI(); //退出登录
			break;
		case 202:
			memset((char*)&Cliuser,0,sizeof(USER));//清空数据防止干扰
			iChoice = CliRegisterUI(&Cliuser); //用户注册
			break;
		case 203:
			memset((char*)&Cliuser,0,sizeof(USER));//清空数据防止干扰
			iChoice = CliForgotUI(&Cliuser); //找回密码
			break;
		}
	}
	return 0;
}
