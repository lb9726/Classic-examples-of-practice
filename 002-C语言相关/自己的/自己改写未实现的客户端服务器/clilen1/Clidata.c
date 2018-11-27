#include "main.h"

//登录时与服务器交互
USER *CliSendto(USER *Cliuser)
{
	int sockfd;
	int stdinfd = 0;
	fd_set rset;
	struct sockaddr_in servaddr;
	int ret;
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5678);
	inet_aton("192.168.16.48",&(servaddr.sin_addr));	
	
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	
		FD_ZERO(&rset);
		FD_SET(stdinfd,&rset);
		FD_SET(sockfd,&rset);
		ret = select(sockfd+1,&rset,NULL,NULL,NULL);
		if(ret <= 0)
		{
			if(errno == EINTR)
			{
//				continue;
			}
			else
			{
//				break;
			}
		}
		if(FD_ISSET(stdinfd,&rset))
		{
			printf("发送\n");
			//USER *Cliuser;
			int len = 0;		
			len = sizeof(USER);
			write(sockfd,(USER *)Cliuser,len);			
		}
		if(FD_ISSET(sockfd,&rset))
		{printf("接收\n");
			USER user; //测试用
			int len;		
			len = read(sockfd,(USER *)&user,sizeof(USER));
			if(len == 0)
			{
//				break;
			}
			ShowUSER(&user);
			write(1,"\n",1);
		}
	close(sockfd);
	exit(0);

}

//登录
USER *CliSend(USER *Cliuser)
{	int sockfd;
	struct sockaddr_in servaddr;
	int len = sizeof(USER);
	USER user;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	servaddr.sin_port = htons(5678);
	inet_aton("192.168.16.48",&(servaddr.sin_addr));

	sendto(sockfd,(USER *)Cliuser,len,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	recvfrom(sockfd,(USER *)&user,len,0,NULL,NULL);

	close(sockfd);
	return Cliuser;
}

int ShowUSER(USER *user)
{
	printf("user.iID = %d\n",user->iID);
	printf("user.szPass = %s\n",user->szPass);
	return 0;
}


//获取地址
//返回IP地址字符串
//返回：0=成功，-1=失败
int getlocalip(char* outip)
{
	int i=0;
	int sockfd;
	struct ifconf ifconf;
	char buf[512];
	struct ifreq *ifreq;
	char* ip;
	//初始化ifconf
	ifconf.ifc_len = 512;
	ifconf.ifc_buf = buf;
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		return -1;
	}
	ioctl(sockfd, SIOCGIFCONF, &ifconf);    //获取所有接口信息
	close(sockfd);
	//接下来一个一个的获取IP地址
	ifreq = (struct ifreq*)buf;
	for(i=(ifconf.ifc_len/sizeof(struct ifreq)); i>0; i--)
	{
		ip = inet_ntoa(((struct sockaddr_in*)&(ifreq->ifr_addr))->sin_addr);
		if(strcmp(ip,"127.0.0.1")==0)  //排除127.0.0.1，继续下一个
		{
			ifreq++;
			continue;
		}
		strcpy(outip,ip);
		return 0;
	}
	return -1;
}

//获取系统时间
void systemtime(USER *Cliuser)
{	
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime( &rawtime );
	sprintf(Cliuser->timestart,"%d/%d/%d %d:%d:%d\n"
	,timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday
	,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
}

