#include"ClientUI.h"

int main(int argc, char *argv[])
{
	int	sockfd;
	int stdinfd = 0;
	fd_set rset;
	struct sockaddr_in	servaddr;
	int ret;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5678);
	inet_aton("127.0.0.1", &servaddr.sin_addr);
	ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(ret < 0)
	{
		perror("connect");
		return -1;
	}
	while(1)
	{
		FD_ZERO(&rset);
		FD_SET(stdinfd,&rset);
		FD_SET(sockfd,&rset);
		ret = select(sockfd + 1,&rset,NULL,NULL,NULL);
		if(ret <= 0)
		{
			if(errno == EINTR) //如果是一个中断信号
			{
				continue;
			}
			else
			{
				break;
			}
		}
		if(FD_ISSET(stdinfd,&rset))
		{
			RegAndLogUI(sockfd);
		}
		if(FD_ISSET(sockfd,&rset))
		{					                             
            char buf[200] = {'\0'};    
            read(sockfd,buf,sizeof(buf));              //接受服务器端返回来的信息	         
            if(strcmp(buf,"注册成功！\n") == 0)
            {
            	printf("%s\n\n",buf);
            	sleep(1);
            	int ret = read(sockfd,buf,sizeof(buf));
            	if(ret < 0)
            	{
            	    printf("服务器连接错误！两秒后自动返回\n");
            	    sleep(2);
            	    RegAndLogUI(sockfd);
            	}
            	printf("%s\n",buf);
            	printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
    			RegAndLogUI(sockfd);
            }
            if(strcmp(buf,"登录成功！\n") == 0)          //用户登录成功,进入功能界面,否则，返回登录注册总界面
    		{  
    			printf("%s\n",buf);    			
                sleep(1);
    			MainUI(sockfd);
    		}
    		else if(strcmp(buf,"登录失败！\n") == 0)
    		{
    			printf("%s\n",buf);
    			printf("Press Any key to continue...\n");
    			while(getchar() == '\n');
    			RegAndLogUI(sockfd);
    		}  
    		if(strcmp(buf,"添加好友成功！\n") == 0)
    		{
    			printf("%s\n",buf);
    			printf("Press Any key to continue...\n");
    			while(getchar()=='\n');
    			MainUI(sockfd);
    		}
    		if(strcmp(buf,"添加好友失败,没有该用户！\n") == 0)
    		{
    		    printf("%s\n",buf);
    		    printf("Press Any key to continue...\n");
    			while(getchar()=='\n');
    			MainUI(sockfd);
    		}
    		if(strcmp(buf,"删除好友成功！\n") == 0)
    		{
    			printf("%s\n",buf);
    			printf("Press Any key to continue...\n");
    			while(getchar()=='\n');
    			MainUI(sockfd);
    		}
    		if(strcmp(buf,"删除好友失败,没有该用户！\n") == 0)
    		{
    		    printf("%s\n",buf);
    		    printf("Press Any key to continue...\n");
    			while(getchar()=='\n');
    			MainUI(sockfd);
    		}
    		if(strcmp(buf,"聊天") == 0)
    		{
    		    PrivateChatUI(sockfd);
    		}
    		if(strcmp(buf,"好友列表！\n") == 0) 
    		{   
    		    system("clear");
    			printf("\n======================好友列表======================\n\n");		
    			printf("%-8s     %-15s     %-8s\n","好友帐号","好友姓名","在线状态");
    			while(1)
    			{
    			    bzero(buf,sizeof(buf));
    			    int len = sizeof(buf);
    				int ret = read(sockfd,buf,len);//好友列表功能有时莫名其妙错误！！！
    				if(ret == 200||ret == 2)
    				{ 	
    				    if(strncmp(buf,"OK",2) != 0)
    				    {
    					    printf("%s",buf);
    				    }
    				    if(strncmp(buf,"OK",2) == 0)
    				    {
    					    break;
    				    }
    			    }
    			    else
    			    {
    			         printf("服务器繁忙！请稍后重试！\n");
    				     break;    				
    			    } 
    			}
    			printf("\nPress Any key to continue...\n");
    			while(getchar() == '\n'); 
    			MainUI(sockfd);  		   			
    		}    		    		     
		}
	}
	close(sockfd);
	exit(0);
}
