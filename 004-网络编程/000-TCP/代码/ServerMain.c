#include"ServerLogic.h"

int getMaxFd(int * pint,int size);
void addFd(int * pint,int size,int fd);
void setAllFd(int * pint,int size,fd_set * fdset);

int main(int argc, char **argv)
{
	int	listenfd, connfd;
	socklen_t clilen;
	struct sockaddr_in	cliaddr, servaddr;
    char buf[20] = {'\0'};
    char bufIP[40] = {'\0'};
	fd_set rset;
	int maxfd;
	int ret;
	int clientfd[64] = {0};
	int i = 0;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(clientfd,0xff,sizeof(clientfd));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	inet_aton("127.0.0.1", &(servaddr.sin_addr));
	servaddr.sin_port        = htons(5678);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, 5);

	maxfd = listenfd;
	for ( ; ; ) 
    {
		FD_ZERO(&rset);
		FD_SET(listenfd,&rset);
		setAllFd(clientfd,64,&rset);
		maxfd = getMaxFd(clientfd,64);
		if(maxfd < listenfd)
		{	
			maxfd = listenfd;
		}
		ret = select(maxfd+1,&rset,NULL,NULL,NULL);
		if(ret <= 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		if(FD_ISSET(listenfd,&rset))
		{
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
			addFd(clientfd,64,connfd);
		}
		for(i = 0; i < 64;i++)
		{
			if(clientfd[i] > 0)
				if(FD_ISSET(clientfd[i],&rset))
				{
					int len;
					MESSAGE msg;
					strcpy(bufIP,inet_ntoa(cliaddr.sin_addr));  //bufIP 存储IP地址 
					strcpy(msg.IP,bufIP);
					msg.clientfd=clientfd[i];
					len = read(clientfd[i],&msg,sizeof(msg));
					if(len == 0)
					{
						close(clientfd[i]);
						clientfd[i] = -1;
						continue;
					}
					
					if(strcmp(msg.flag,"注册")==0)
					{
					    RegisterCheck(clientfd[i],msg);		          
					}
					
					if(strcmp(msg.flag,"登录")==0)
					{
					    LoginCheck(clientfd[i],msg);		                      
					}
					
				    if(strcmp(msg.flag,"好友列表")==0)
                    {
                        FriendList(clientfd[i],msg);       
                    }
                   
				    if(strcmp(msg.flag,"添加好友")==0)
                    {
                        AddFriend(clientfd[i],msg);
                    }
                    
                    if(strcmp(msg.flag,"删除好友")==0)
                    {
                        DelFriend(clientfd[i],msg);
                    }
                    
                    if(strcmp(msg.flag,"聊天")==0)
                    {                      
                        write(clientfd[i],msg.flag,sizeof(msg.flag));
                    }
                    
                    if(strcmp(msg.flag,"私聊")==0)
                    {
                        HandlePerChat(clientfd[i],msg);
                    }
                    if(strcmp(msg.flag,"群聊")==0)
                    {
                        HandleGroChat(clientfd[i],msg);
                    }
                    
                    if(strcmp(msg.flag,"退出")==0)
                    {
                        ExitChat(clientfd[i],msg);
                    }    
                    					
				}
			}
		
	}
    close(listenfd);
	return 0;
}

int getMaxFd(int * pint,int size)
{
	int max = pint[0];
	int i = 0;
	for(i=1;i < size;i++)
	{
		if(max < pint[i])
		{
			max = pint[i];
		}
	}
	return max;
}

void addFd(int * pint,int size,int fd)
{
	int i = 0;
	for(i = 0; i < size;i++)
	{
		if(-1 == pint[i])
		{
			pint[i] = fd;
			break;
		}
	}	
}
void setAllFd(int * pint,int size,fd_set * fdset)
{
	int i = 0;
	for(i = 0; i < size;i++)
	{
		if(-1 != pint[i])
		{
			FD_SET(pint[i],fdset);
		}
	}	
	
}
