#include "serverdata.h"

//读文件到链表的子函数
STNODE * readfiletolist(char filename[30])
{
	STNODE *head=(STNODE *)malloc(sizeof(STNODE));
	head->next==NULL;
	USER client;
	FILE *file=fopen(filename,"rt");
    if(file==NULL)
    {
        printf("打开文件%s出错！\n",filename);
        return;
    }
    else
    {
        while((fread(&client,sizeof(USER),1,file))==1)//利用尾插法将文件中读取的信息临时存储在链表中
        {
            STNODE *p=(STNODE *)malloc(sizeof(STNODE));//创建一个新结点p
                STNODE *tmp=head;
                while(tmp->next!=NULL)  //将指针移动到链表的尾部，即最后一个元素的地方
                    tmp=tmp->next;
                tmp->next=p;
                p->next=NULL;
                p->user=client;
        }//end of while   
    }// end of else
    fclose(file);
    return head;
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

//自动生成注册用户的ID编号
int readlinklistID(STNODE *head)
{
    STNODE *p=head->next;
    int bianhaoID;
    if(p == NULL)
    {
        return 10000;
    }
    bianhaoID=p->user.iID;
    while(p->next!=NULL)
    {	
    	if(p->next->user.iID>bianhaoID)
    		bianhaoID=p->next->user.iID;
    	p=p->next;	
    }
    printf("%d\n",bianhaoID);
    bianhaoID=bianhaoID+1;
    printf("%d\n",bianhaoID);
    return bianhaoID;
 }
 
 //注册用户信息界面
STNODE * AdduserUI(STNODE *head)
{
	STNODE *p=(STNODE*)malloc(sizeof(STNODE));//1-1创建一个新结点p
    STNODE *tmp = head;
    p->user.iID=readlinklistID(head);//////bug
    while(tmp->next!=NULL)//将指针移动到链表的尾部，即最后一个元素的地方
    	tmp=tmp->next;
    tmp->next=p;
    p->next=NULL;
	
	printf("请输入用户名："); 
	scanf("%s",p->user.szName);
	fflush(stdin);
	printf("请输入用户密码：");
	scanf("%s",p->user.szPass);
	fflush(stdin);
	printf("请输入用户的密保问题：");
	scanf("%s",p->user.szAnswer);
	fflush(stdin);
	systemtime();
	strcpy(p->user.timeregist,systime);//系统时间调用
	fflush(stdin);
	return head;
}

 //返回给客户端一个注册的编号信息
USER * returnclient(STNODE *head,USER *client)
{
	client->iID = readlinklistID(head);
	return client;
}
 
//登录时用链表对比信息是否正确
USER  logincompare(STNODE *head,USER client)
{
	STNODE *p=head->next;
    while(p!=NULL)
    {
    	if((client.iID==p->user.iID) && strcmp(client.szPass,p->user.szPass))
    	{
    		client=&p->user;
    		return client;
    	}
    	p=p->next;
    }
    printf("用户名或密码错误,请重新输入!!\n");
}

//找回密码
USER * findpasswd(STNODE *head,USER *client)
{
	STNODE *p=head->next;
    while(p!=NULL)
    {
    	if((client->iID==p->user.iID) && strcmp(client->szAnswer,p->user.szAnswer))
    	{
    		client=&p->user;
    		return client;//返回这个结构体,密码在调用的地方打印一下即可
    	}
    	p=p->next;
    }
}

//客户修改密码的处理
STNODE * Modifypasswd(STNODE *head,USER *client)
{
	STNODE *p=head->next;
    while(p!=NULL)
    {
    	if(client->iID==p->user.iID)
    	{
    		strcpy(client->szPass,p->user.szPass);
    		return head;
    	}
    	p=p->next;
    }
}

//服务器保存文件
void savefile(STNODE *head,char filename[30])
{
	STNODE *p=head->next;
	FILE *fp;
	fp=fopen(filename,"wt");
	if(fp == NULL)
	{
		printf("文件%s打开错误!!\n",filename);
		return;
	}
    while(p!=NULL)
    {
    	fwrite(&p->user,sizeof(p->user),1,fp);
    	p=p->next;
    }
    printf("用户修改的信息保存成功!!\n");
}

void print(STNODE *head)
{
	STNODE *p=head->next;
	printf("\t%-12s %-20s %-20s %-20s\n",    "编号","用户名","密码","注  册  时  间");
	while(p!=NULL)
	{
		printf("\t%-10d %-19s %-18s %-20s\n",p->user.iID,p->user.szName,p->user.szPass,p->user.timeregist);
		p=p->next;
	}
}
/*
int main()
{   
	int ret;
	STNODE *head=NULL;
	head=readfiletolist("user.txt");
	printf("%p主函数读完文件之后的head的next\n",head->next);
    while(1)
    {
    	printf("请输入2 或 1\n");
    	scanf("%d",&ret);
	    switch(ret)
	    {
		   case 1:
		    	head=AdduserUI(head);
		   		break;
		    case 2:
		    	savefile(head,"user.txt");
		    	break;
	       case 3:
		    	print(head);
            
		    	break;
           /*  case 4:
                searchnameorID(head);
		    	break; 
			case 5:
                showdicinfo(head);
                rethome();
		    	break; 
        }
             if(0==ret)
             	exit(0);
	}
    return 0;
}
 */









