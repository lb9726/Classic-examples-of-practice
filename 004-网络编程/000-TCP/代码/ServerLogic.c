#include"ServerLogic.h"

int RegisterCheck(int clientfd,MESSAGE message)       //注册判断函数
{
    int n,num;
    char buf[50];
    srand((unsigned)time(NULL));
    STlinkreadRegInfofile();
    while(1)
    {
        num=rand()%9999;
        if(num>=1000)
         {
            n=CoverRegNode(num);
            if(n!=0)
                break;
         }       
    }
    message.pnum=num;
    addSTlinklist(message);
    writeRegInfofile();
    DestoryLinklist();
    strcpy(buf,"注册成功！\n");
    write(clientfd,buf,sizeof(buf));
    sprintf(buf,"你的帐号是：%d\n",num);
    write(clientfd,buf,sizeof(buf));
}

int LoginCheck(int clientfd,MESSAGE message)             //登录判断函数
{    
    int n;
    char buf[50];
    STlinkreadRegInfofile();
    n=CoverLogNode(message);
    DestoryLinklist();  
    if(n==1)
    {   
        UpdateStartIP(message); 
	    strcpy(buf,"登录成功！\n");	
	    write(clientfd,buf,sizeof(buf));		                      
	}
    else
	{
		strcpy(buf,"登录失败！\n");
		write(clientfd,buf,sizeof(buf)); 
	}	        
}
