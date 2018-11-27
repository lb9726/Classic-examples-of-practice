#include "File.h"
#include "serverdata.h"

int main(int argc,char *argv[])
{
	STNODE *stHead;
	STNODE *head;
	stHead->next = NULL;
	//ReadUSERFile(stHead);  //读文件
	head=readfiletolist("user.txt");
	int serverfd;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	USER Seruser; //
	int len = sizeof(USER);
	
	serverfd = socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_aton("192.168.16.48",&(servaddr.sin_addr));
	servaddr.sin_port = htons(5678);
	
	bind(serverfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	while(1)
	{
		clilen = sizeof(cliaddr);
		recvfrom(serverfd,(USER *)&Seruser,len,0,(struct sockaddr *)&cliaddr,&clilen);
		//接收到客户端发来的信息
		printf("接收的数据为：\n");
		Showuser(&Seruser);
	
		Judgelogic(head,Seruser);
	
		sendto(serverfd,(USER *)&Seruser,len,0,(struct sockaddr *)&cliaddr,clilen);
	}
	close(serverfd);
		
	return 0;
   
}


//处理传来的数据
void Judgelogic(STNODE *head,USER Seruser)
{
	CHAT Serchat;
	int index = Seruser->iNum;
	switch(index)
	{
	case 201:
		//Showuser(Seruser);
		Seruser=logincompare(head,Seruser);
		//用户登录验证函数
		break;
	case 202:
		//用户注册验证函数
		break;
	case 203:
		//用户找回密码验证函数
		findpasswd(head,Seruser);
		break;
/*	case 51:
		//调用单人聊天进程
		Serchat = Seruser->chat;
		Addonecaht(&Serchat); //写到文件末尾函数
		break;
	case 52:
		//调用群聊进程
		Serchat = Seruser->chat;
		Addgroupcaht(&Serchat); //写到文件末尾函数
		break;*/
	case 53:
		//用户修改密码
		Modifypasswd(head,Seruser);
		break;
	case 54:
		//用户删除聊天记录
		break;
	case 55:
		//上传下载文件	
		break;
	case 56:
		//退出登录 函数
		break;
	}
}

