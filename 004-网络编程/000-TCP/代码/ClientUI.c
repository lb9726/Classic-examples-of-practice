#include"ClientUI.h"



char timebuf[50];

//1.登录界面
int LoginUI(int sockfd)
{
	MESSAGE Client;
	system("clear");
    printf("==================登录界面========================\n\n");  
    printf("\t帐号：");
    scanf("%d",&Client.pnum);    
    printf("\t密码：");
    scanf("%s",Client.msg);
    printf("-----------------------------------\n");
    pnum0=Client.pnum;                            //用全局变量保存登录者的帐号
   	strcpy(Client.flag,"登录");   	
   	system("clear"); 
    printf("正在连接服务器，请稍等.\n"); 
    sleep(1); 
    system("clear"); 
    printf("正在连接服务器，请稍等..\n"); 
    sleep(1); 
    system("clear"); 
    printf("正在连接服务器，请稍等...\n"); 
    sleep(1);   	
    write(sockfd,&Client,sizeof(Client));        //向服务器发送信息，请求登录 
	return ;	
}


//2.注册界面
int RegisterUI(int sockfd)
{
    system("clear");
    MESSAGE Client;
    char passwd[1000];
    printf("==================注册界面========================\n\n");  
    do
    {     	
     	printf("\t请输入用户名（在10字以内）：");
        scanf("%s",Client.name);     
    }while(strlen(Client.name)>20 || strlen(Client.msg)>20);
    while(1)
    {
        printf("\t请输入密码（在20位以内）：");
     	scanf("%s",Client.msg);
     	printf("\t请再次输入密码（在20位以内）：");
     	scanf("%s",passwd);
     	if(strcmp(Client.msg,passwd)!=0 || strlen(Client.msg)>20 ||strlen(passwd)>20)
     	{
     	    printf("密码出错！\n");
     	}
        else
       	{
     	    break;
     	}
    }
    printf("\n-----------------------------------\n");
    strcpy(Client.flag,"注册");
    system("clear"); 
    printf("正在连接服务器，请稍等...\n"); 
    sleep(2); 
    write(sockfd,&Client,sizeof(Client));      //向服务器发送信息，请求注册
    return ;
}


//3.登录注册总界面
int RegAndLogUI(int sockfd)
{
	int iChoice;  
    do  
    {  
        system("clear");  
        printf("===============欢迎进入聊天室==============\n");  
        printf("\t1.登录                \n");  
        printf("\t2.注册                \n");  
        printf("\t0.退出                \n");  
        printf("-------------------------------\n");  
        printf("请选择:");   
        scanf(" %d",&iChoice);    
    }while((iChoice != 1) && (iChoice != 2) && (iChoice != 0));  
    switch(iChoice)
    {
    	case 1:
    		LoginUI(sockfd);
    		break;
    	case 2:
    		RegisterUI(sockfd);
    		break;
    	case 0:
    		Exit(sockfd);
    }
    return iChoice;   
}


//4.好友列表界面
int GoodFriendUI(int sockfd)
{
	MESSAGE Client;
	Client.pnum=pnum0; 
	strcpy(Client.flag,"好友列表");	
	write(sockfd,&Client,sizeof(Client));      //向服务器发送信息，请求好友列表	
}

//5.添加好友界面
int AddFriendUI(int sockfd)
{
	MESSAGE Client;
	printf("\n===================添加好友界面====================\n\n");
	printf("请输入要添加的好友帐号：");
	scanf("%d",&Client.num);
	strcpy(Client.flag,"添加好友");
    Client.pnum=pnum0;                              //登录者的帐号添加到好友列表的首项（归属者）
	write(sockfd,&Client,sizeof(Client));          //向服务器发送信息，请求添加好友 	
} 

//6.删除好友界面
int DelFriendUI(int sockfd)
{
    MESSAGE Client;
	printf("\n===================删除好友界面====================\n\n");
	printf("请输入要删除的好友帐号：");
	scanf("%d",&Client.num);
	strcpy(Client.flag,"删除好友");
    Client.pnum=pnum0;                              //登录者的帐号添加到好友列表的首项（归属者）
	write(sockfd,&Client,sizeof(Client));          //向服务器发送信息，请求删除好友 	
}             

//7.0客户端聊天开始
int ClientChatUI(int sockfd)
{
    MESSAGE Client;
    strcpy(Client.flag,"聊天");
    write(sockfd,&Client,sizeof(Client));
}

//7.聊天主界面
int PrivateChatUI(int sockfd)
{
	system("clear");
	int iChoice;
	printf("===============聊天选项==============\n");  
	printf("\t1.私聊\n");
	printf("\t2.群聊\n");
	printf("\t3.查看聊天记录\n");
	printf("\t0.返回\n");
	printf("=====================================\n");
	printf("\t请选择:");
	scanf("%d",&iChoice);
	switch(iChoice)
	{
		case 1:
			ChatUI(sockfd);
			break;
		case 2:
			GroupChatUI(sockfd);
			break;
		case 3:
			Record(sockfd);
			break;
		case 0:
			MainUI(sockfd);
			break;
	}		
}            

//8.私聊界面
int ChatUI(int sockfd)
{
     char buf[100];
	 MESSAGE Client={'\0'};
	 strcpy(Client.flag,"私聊");
  	 printf("输入好友帐号:");
	 scanf("%d",&Client.num);
	 Client.pnum=pnum0;	
     printf("==============当前为聊天界面==============\n");
     pid_t pid;
     pid=fork();
     
     if(pid>0)
     {

         while(1)
         {
    	      scanf("%s",Client.msg);
    	      gettime();
    		  sprintf(buf,"%d>>>:%s",Client.pnum,Client.msg);
    		  FILE *fp;
              fp=fopen("PchatRecord.txt","a");
    		  flock(fp->_fileno, LOCK_EX); 
    		  fprintf(fp,"%-4d  %-4d  %-8s  %-50s\n",Client.pnum,Client.num,timebuf,buf);
    		  fclose(fp);
    		  flock(fp->_fileno, LOCK_UN); 
    		  write(sockfd,&Client,sizeof(Client));
    		  if(strncmp(Client.msg,"quit",4)==0)
    	      {
    	           printf("\n聊天结束!\n");
    	           printf("\n5秒后自动返回！\n");    	         
    	           break;
    	      } 
    	 }    	 		
     }
     if(pid==0)
     {

    	 while(1)
    	 {   
    		  int ret=read(sockfd,Client.msg,sizeof(Client.msg));
    		 // printf("ret=%d\n",ret);
    		  gettime();   
    		  FILE *fp;
              fp=fopen("PchatRecord.txt","a");
    		  flock(fp->_fileno, LOCK_EX); 
    		  fprintf(fp,"%-4d  %-4d  %-8s  %-50s\n",Client.pnum,Client.num,timebuf,Client.msg);
    		  fclose(fp);
    		  flock(fp->_fileno, LOCK_UN);  
    		  if(ret>0)
    		  {
    		       printf("%s\n",Client.msg);
    		  }    
    		  if(strncmp(Client.msg,"quit",4)==0)
    	      {
    	           printf("对方退出!聊天结束:（quit）\n");       	         
    	           break;
    	      } 
    	  }
    	  exit(0); 
    	     	
     }

     sleep(5);
     MainUI(sockfd);     	
    
}

//9.聊天记录界面
int Record(int sockfd)
{
     MESSAGE msg;
     int pnum,num;
     int ch;
     char buf[100];
     printf("=====================================\n\n");
  	 printf("请输入选项（1：查看全部 2：部分 0：返回 ）：");
  	 scanf("%d",&ch);
  	 if(ch==1)
  	 {
  	    pnum=pnum0;
  	    num=pnum0;
  	 }
  	 if(ch==2)
  	 { 	
  	    printf("请输入与之聊天好友帐号："); 
	    scanf("%d",&num);
	    pnum=pnum0;	
	 }   
	 if(ch==0)
	 {
	    MainUI(sockfd);
	 }
     system("clear");
     printf("================当前为聊天记录界面================\n\n");
     printf("%-4s  %-4s  %-25s      %-50s\n\n","发起人","接收者","聊天时间","聊天内容");

     FILE *fp;
     fp=fopen("PchatRecord.txt","r");
 
     while( (fscanf(fp,"%d",&msg.pnum))>0)
     {
         fscanf(fp,"%d",&msg.num);
         fscanf(fp,"%s",msg.name); 
         fscanf(fp,"%s",msg.flag); 
         fscanf(fp,"%s",msg.msg);
         if(ch==1&&msg.pnum==pnum)
         {
            if(msg.num==999)
            {
                strcpy(buf,"all");
                printf("%-6d  %-6s  %-15s  %-8s  %-50s\n",msg.pnum,buf,msg.name,msg.flag,msg.msg);
            }
            else
            {
                printf("%-6d  %-6d  %-15s  %-8s  %-50s\n",msg.pnum,msg.num,msg.name,msg.flag,msg.msg);
            }      
         }	
         if(ch==2)
         {
            if(msg.num==num&&msg.pnum==pnum)
            {
                printf("%-6d  %-6d  %-15s  %-8s  %-50s\n",msg.pnum,msg.num,msg.name,msg.flag,msg.msg);
            }
         }
     }
     fclose(fp);
     printf("Press Any key to continue...\n");
     while(getchar()=='\n');
     MainUI(sockfd);
}

 //10.群聊界面
int GroupChatUI(int sockfd)
{
    MESSAGE Client={'\0'};
    char buf[100];
	strcpy(Client.flag,"群聊");
	Client.pnum=pnum0;	
	Client.num=999;
    printf("===========当前为群聊界面===============\n\n");
     pid_t pid;
     pid=fork();
     
     if(pid>0)
     {

         while(1)
         {
    	      scanf("%s",Client.msg);
    		  write(sockfd,&Client,sizeof(Client));
    		  if(strncmp(Client.msg,"quit",4)==0)
    	      {
    	           printf("\n聊天结束!\n");
    	           printf("\n5秒后自动返回！\n");    	         
    	           break;
    	      } 
    	 }    	 		
     }
     if(pid==0)
     {

    	 while(1)
    	 {   
    		  int ret=read(sockfd,Client.msg,sizeof(Client.msg));
    		  gettime();   
    		  FILE *fp;
              fp=fopen("PchatRecord.txt","a");
    		  flock(fp->_fileno, LOCK_EX); 
    		  fprintf(fp,"%-4d  %-4d  %-8s  %-50s\n",Client.pnum,Client.num,timebuf,Client.msg);
    		  fclose(fp);
    		  flock(fp->_fileno, LOCK_UN);  
    		  if(ret>0)
    		  {
    		       printf("%s\n",Client.msg);
    		  }    
    		  if(strncmp(Client.msg,"quit",4)==0)
    	      {
    	           printf("对方退出!聊天结束:（quit）\n");       	         
    	           break;
    	      } 
    	  }
    	  exit(0); 
    	     	
     }
     sleep(5);
     MainUI(sockfd);     	
}       


//11.退出界面
int Exit(int sockfd)
{
	MESSAGE Client;
	strcpy(Client.flag,"退出");
	Client.pnum=pnum0;
	write(sockfd,&Client,sizeof(Client));
	close(sockfd);
	exit(0);	
}
//12.功能主界面
int MainUI(int sockfd)
{
	int iChoice;
	do
	{
		system("clear");
		printf("==================主界面==================\n\n");
		printf("\t1.好友列表           \n");
		printf("\t2.添加好友           \n");
		printf("\t3.删除好友           \n");
		printf("\t4.聊    天           \n");
		printf("\t0.退    出           \n");
		printf("==========================================\n\n");
		printf("请选择(0~4):");
		scanf("%d",&iChoice);
	}while((iChoice != 1) && (iChoice != 2) && (iChoice != 3) && (iChoice != 4)  && (iChoice != 0));
	switch(iChoice)
	{
		case 1:
			GoodFriendUI(sockfd);
			break;
		case 2:
			AddFriendUI(sockfd);
			break;
		case 3:		 
		    DelFriendUI(sockfd);
			break;	
		case 4:		 
		    ClientChatUI(sockfd);
			break;	
		case 0:
			Exit(sockfd);
			break;	
	}
	return 0;
}                   

//13，获取时间函数
int gettime()
{
    time_t timep;  
    struct tm *p;  
    time(&timep);  
    p =localtime(&timep);
    strftime(timebuf,50,"Data:%F %T",p);
}














