#include"ServerData.h"

int quitnum=0;

int DestoryLinklist()                           //1,销毁链表      
{
    STHandle *p=head.next;
    while(p!=NULL)
    {
       head.next=p->next;
       p=head.next;
    }
    return;
}

int addSTlinklist(MESSAGE message)               //2,添加注册人员信息链表  for RegInfoTab.txt and PerInfoTab.txt
{
    STHandle *pnode=malloc(sizeof(STHandle));
    pnode->message=message;
    pnode->next=NULL;
        
    if(NULL==head.next)
        head.next=pnode;
    else
    {
        STHandle *tmp=head.next;
        while(tmp->next!=NULL)
        {
            tmp=tmp->next;
        }
        tmp->next=pnode;
    }
}

int STlinkreadRegInfofile()                      //3,链表读取文件RegInfoTab.txt
{
     MESSAGE message;
     FILE *fp;
     fp=fopen("RegInfoTab.txt","r");
     while( (fscanf(fp,"%d",&message.pnum))>0)
     {
         fscanf(fp,"%s",message.name);
         fscanf(fp,"%s",message.msg);
         addSTlinklist(message);	
     }
     fclose(fp);
}

int STlinkreadPerInfofile()                      //4,链表读取文件PerInfoTab.txt
{
     MESSAGE message;
     FILE *fp;
     fp=fopen("PerInfoTab.txt","r");
     while( (fscanf(fp,"%d",&message.pnum))>0)
     {
         fscanf(fp,"%d",&message.num);
         fscanf(fp,"%s",message.name); 
         fscanf(fp,"%d",&message.state);
         fscanf(fp,"%d",&message.clientfd);
         fscanf(fp,"%s",message.IP);
         addSTlinklist(message);	
     }
     fclose(fp);
}

int  CoverRegNode(int num0)                     //5,遍历  for 注册
{
    MESSAGE message;
    int flag=1;
    STHandle *p=head.next; 
    while(p!=NULL)
    { 
         if(p->message.num==num0) 
         {
            flag=0;
            break;
         }         
         p=p->next;   
    }
    return flag;   
}

int  CoverLogNode(MESSAGE message)              //6,遍历  for 登录
{
  
    int flag=0;
    STHandle *p=head.next; 
    while(p!=NULL)
    { 
         if(p->message.pnum==message.pnum&&strcmp(p->message.msg,message.msg)==0) 
         {
            strcpy(pname,p->message.name); 
            flag=1;
            break;
         }         
         p=p->next;   
    }
    return flag;   
}

int  CoverAddFNode(MESSAGE message)             //7,遍历  for 添加好友
{
  
    int flag=0;
    message.state=0;      //"0"表示不在线，默认不在线
    STHandle *p=head.next; 
    FILE *fp;
    fp=fopen("PerInfoTab.txt","a");
    while(p!=NULL)
    { 
         if(p->message.pnum==message.num) 
         {
            fprintf(fp,"%-8d %-8d %-15s %-8d %-8d %-8s\n",message.pnum,p->message.pnum      //A 加 B好友
                                                   ,p->message.name,message.state,-1,"1"); 
                                                   
            fprintf(fp,"%-8d %-8d %-15s %-8d %-8d %-8s\n",p->message.pnum,message.pnum     ////B 加 A好友
                                                   ,pname,message.state,-1,"1"); 
            flag=1;
            break;
         }         
         p=p->next;   
    }
    fclose(fp);
    return flag;   
}

int  CoverDelFNode(MESSAGE message)        //8,遍历  for 删除好友
{
  
    int flag=0;
    message.state=0;      //"0"表示不在线，默认不在线
    STHandle *p=head.next; 
    FILE *fp;
    fp=fopen("PerInfoTab.txt","w");
    while(p!=NULL)
    { 
        if(p->message.pnum==message.pnum&&p->message.num==message.num ||
           p->message.pnum==message.num&&p->message.num==message.pnum)
         {
               flag=1;
         }
         else
         {
              fprintf(fp,"%-8d %-8d %-15s %-8d %-8d %-8s\n",p->message.pnum,p->message.num      
                                                           ,p->message.name,p->message.state
                                                           ,p->message.clientfd,p->message.IP);
         }  
         p=p->next;                                        
    }
    fclose(fp);
    return flag;   
}

int UpdateStartIP(MESSAGE message)                    //9,开始时，更新IP
{
    STlinkreadPerInfofile();               //链表读取文件PerInfoTab.txt
     
    STHandle *p=head.next; 
    FILE *fp;
    fp=fopen("PerInfoTab.txt","w");
    while(p!=NULL)
    { 
         message.state=0;
         if(p->message.num==message.pnum) 
         {
            message.state=1;                                      
            fprintf(fp,"%-8d %-8d %-15s %-8d %-8d %-8s\n",p->message.pnum,p->message.num     
                                                   ,p->message.name,message.state,message.clientfd,message.IP);
         } 
         else
         {
            fprintf(fp,"%-8d %-8d %-15s %-8d %-8d %-8s\n",p->message.pnum,p->message.num      
                                                   ,p->message.name,p->message.state
                                                   ,p->message.clientfd,p->message.IP); 
         }        
         p=p->next;
         // printf("p->message.num=%d\n",p->message.num);  
         //printf("message.pnum=%d\n",message.pnum);   
         //printf("message.IP=%s\n",message.IP); 
    }
    fclose(fp);
    DestoryLinklist();
}

int UpdateEndIP(MESSAGE message)                                //9.1,开始更新IP
{
    STlinkreadPerInfofile();               //链表读取文件PerInfoTab.txt
     
    STHandle *p=head.next; 
    FILE *fp;
    fp=fopen("PerInfoTab.txt","w");
    while(p!=NULL)
    { 
         message.state=0;
         if(p->message.num==message.pnum) 
         {                                     
            fprintf(fp,"%-8d %-8d %-15s %-8d %-8d %-8s\n",p->message.pnum,p->message.num     
                                                   ,p->message.name,message.state,-1,"1");
         } 
         else
         {
            fprintf(fp,"%-8d %-8d %-15s %-8d %-8d %-8s\n",p->message.pnum,p->message.num      
                                                         ,p->message.name,p->message.state
                                                         ,p->message.clientfd,p->message.IP); 
         }        
         p=p->next;
         // printf("p->message.num=%d\n",p->message.num);  
         //printf("message.pnum=%d\n",message.pnum);   
         //printf("message.IP=%s\n",message.IP); 
    } 
    fclose(fp);
    DestoryLinklist();
}
int  CoverFriListNode(MESSAGE message,int sockfd)        //10,遍历  for 好友列表
{
    MESSAGE msg;
    char buf[200]={'\0'};
    char buf2[20];
    STHandle *p=head.next; 
    while(p!=NULL)
    { 
         if(p->message.pnum==message.pnum) 
         {
        
            msg.num=p->message.num;         
            strcpy(msg.name,p->message.name);
            msg.state=p->message.state;
            if(msg.state==1)
            {
                strcpy(buf2,"在线");
            }
            else
            {
                strcpy(buf2,"离线");
            }
            sprintf(buf,"%-8d     %-15s     %-8s\n",msg.num,msg.name,buf2);
            //printf("msg.num=%d\n",msg.num);
            //printf("msg.name=%s\n",msg.name);
            //printf("msg.state=%d\n",msg.state);
            int len=strlen(buf);
            //printf("len=%d\n",len);
            int ret=write(sockfd,buf,sizeof(buf));
            //printf("ret=%d\n",ret);
            //sleep(1);
         }         
         p=p->next;   
    }
    bzero(buf,sizeof(buf));
    strcpy(buf,"OK");
    write(sockfd,buf,strlen(buf));
    //printf("OK\n");
}

int writeRegInfofile()                                          //11,链表写入文件RegInfoTab.txt
{
    FILE *fp;
    fp=fopen("RegInfoTab.txt","w");
    STHandle *p=head.next;
    while(p!=NULL)
    {
       fprintf(fp,"%-8d  %-15s  %-8s\n",p->message.pnum,p->message.name,p->message.msg);                  
       p=p->next;
    }
    fclose(fp);
}


int HandlePerChat(int clientfd,MESSAGE msg)                      //12，处理私人聊天函数
{
    char buf[100];
    int clientfd1=clientfd;       //本人客户端号
    int clientfd2;                //好友客户端号
    clientfd2=getclient(msg);     
    printf("clientfd2=%d\n",clientfd2);
    printf("clientfd1=%d\n",clientfd1);       
    //read(clientfd1,buf1,sizeof(buf1));
    if(strncmp(msg.msg,"quit",4)!=0)
    {
        sprintf(buf,"%d>>>:%s",msg.pnum,msg.msg);
        printf("msg.name=%s\n",msg.name);
        write(clientfd2,buf,sizeof(buf));
        printf("%d>>>:%s\n",msg.pnum,msg.msg);
    }
    else
    {
        write(clientfd1,msg.msg,sizeof(msg.msg));
        write(clientfd2,msg.msg,sizeof(msg.msg));
    }    
}

int HandleGroChat(int clientfd,MESSAGE msg)                      //12.1，处理群组聊天函数
{
    char buf[100];
    char buf2[1000];
    int clientfd1=clientfd;           //本人客户端号
    int clientfdz[50];                //好友客户端号
    int i,n,k,j,l;
    i=0;
    STlinkreadPerInfofile();               //链表读取文件PerInfoTab.txt     
    STHandle *p=head.next; 
    FILE *fp;
    fp=fopen("PerInfoTab.txt","r");
    while(p!=NULL)
    { 
         if(p->message.clientfd!=-1) 
         {
             clientfdz[i]=p->message.clientfd;
             i++;
         }         
         p=p->next;
    }
    fclose(fp);
    DestoryLinklist();
    for(k=0;k<i;k++)
    {
        for(j=k+1;j<i;j++)
        {
            if(clientfdz[j]==clientfdz[k])
            {
                for(l=j;l<i-1;l++)
                {
                    clientfdz[l]=clientfdz[l+1];
                }
                i--;
            }
        }
    }
         
   for(n=0;n<i;n++)
   {
       if(strncmp(msg.msg,"quit",4)!=0)
       {
            sprintf(buf,"%d>>>:%s",msg.pnum,msg.msg);
            printf("msg.name=%s\n",msg.name);
            write(clientfdz[n],buf,sizeof(buf));
            printf("%d>>>:%s\n",msg.pnum,msg.msg);
        }
        else
        {
            write(clientfdz[n],msg.msg,sizeof(msg.msg));
        } 
    }
}

int getclient(MESSAGE msg)                                      //12.2  获取客户端号
{
    int clientfd;
    STlinkreadPerInfofile();               //链表读取文件PerInfoTab.txt     
    STHandle *p=head.next; 
    FILE *fp;
    fp=fopen("PerInfoTab.txt","r");
    while(p!=NULL)
    { 
         if(p->message.pnum==msg.pnum&&p->message.num==msg.num) 
         {
             clientfd=p->message.clientfd;
             break;
         }         
         p=p->next;
    }
    fclose(fp);
    DestoryLinklist();
    return clientfd;
}

int ExitChat(int clientfd,MESSAGE msg)                     //13,退出聊天
{
    UpdateEndIP(msg);
}

int FriendList(int clientfd,MESSAGE msg)                   //14,好友列表
{
    char buf[50];
    strcpy(buf,"好友列表！\n");
    write(clientfd,buf,sizeof(buf));	
    STlinkreadPerInfofile();
    CoverFriListNode(msg,clientfd); 
    DestoryLinklist();
}

int AddFriend(int clientfd,MESSAGE msg)                    //15,添加好友
{
    char buf[50];
    STlinkreadRegInfofile();
    int n=CoverAddFNode(msg);
    DestoryLinklist();
    if(n==1)
    {
        UpdateStartIP(msg); 
        strcpy(buf,"添加好友成功！\n");
        write(clientfd,buf,strlen(buf));
    }
    else
    {
        strcpy(buf,"添加好友失败,没有该用户！\n");
        write(clientfd,buf,strlen(buf));
    }
}

int DelFriend(int clientfd,MESSAGE msg)                    //16,删除好友
{
    char buf[50];
    STlinkreadPerInfofile();
    int n=CoverDelFNode(msg);
    DestoryLinklist();
    if(n==1)
    {
        strcpy(buf,"删除好友成功！\n");
        write(clientfd,buf,strlen(buf));
    }
    else
    {
        strcpy(buf,"删除好友失败,没有该用户！\n");
        write(clientfd,buf,strlen(buf));
    }
}


