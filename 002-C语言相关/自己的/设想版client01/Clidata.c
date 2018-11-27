#include "main.h"

//登录时与服务器交互
USER *CliSend(USER *Cliuser)
{
	int sockfd;
	struct sockaddr_in servaddr;
	int len = sizeof(USER);
	
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	servaddr.sin_port = htons(5678);
	inet_aton("192.168.16.48",&(servaddr.sin_addr));

	sendto(sockfd,(USER *)Cliuser,len,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	recvfrom(sockfd,(USER *)Cliuser,len,0,NULL,NULL);

	close(sockfd);
	return Cliuser;
}

static char systime[30];
//获取系统时间
void systemtime()
{
	
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime( &rawtime );
	sprintf(systime,"%d/%d/%d %d:%d:%d\n",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
}



















