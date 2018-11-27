#include"ui.h"
#include"data.h"
//主界面
int  MainUI()
{
    int iChoice = 0;
    system("clear");     
    printf("\n\t****************************************************************\n");
    printf("\t*                                                              *\n");
    printf("\t           ——————欢迎使用协议缩写小字典——————                  \n");
    printf("\t*                                                              *\n");
    printf("\t****************************************************************\n");
    printf("\t                                                                \n");
    printf("\t                       相关操作选项                           \n");
    printf("\t                                                                \n");
    printf("\t****************************************************************\n");
    printf("\t*                     0.安全退出系统                           *\n");
    printf("\t*                     1.添加字典内容                           *\n");
    printf("\t*                     2.删除字典内容                           *\n");
    printf("\t*                     3.修改字典内容                           *\n");
    printf("\t*                     4.查找字典内容                           *\n");
    printf("\t*                     5.显示字典内容                           *\n");
    printf("\t****************************************************************\n");

    printf("请输入功能编号1~6, 0 表示退出:");
    scanf("%d",&iChoice);
    return iChoice;
}

//添加字典信息
STNODE * AdddicinfoUI(STNODE *head)
{
	STNODE *p=(STNODE*)malloc(sizeof(struct STNODE));//1-1创建一个新结点p
    STNODE *tmp = head;
    while(tmp->next!=NULL)//将指针移动到链表的尾部，即最后一个元素的地方
    	tmp=tmp->next;
    tmp->next=p;
    p->next=NULL;
	p->diction.ID=readfileID(head);
	printf("请输入缩写的字符：");
	scanf("%s",p->diction.simpname);
	fflush(stdin);
	printf("请输入全称：");
	scanf("%s",p->diction.wholename);
	fflush(stdin);
	printf("请输入中文解释：");
	scanf("%s",p->diction.chinesename);
	fflush(stdin);
	//fwrite(&p->diction,sizeof(struct dictionary),1,fp);
	//注释这条代码是为了在退出时进行保存操作而不是每次添加以后就直接写入了文件中
	return head;
}

//删除字典信息
STNODE * deletedicinfo(STNODE *head)
{
	STNODE *t=NULL;
	char ch;
	int confirm=0;
	t=findfordelete(head);//查找到了要删除的地址
	if(t==NULL)
		return head;//地址为空时直接返回head
	printf("请输入confirm的值 1:表示确认删除 0:表示不删除!!! \n");
	confirm=inputdigit01(ch);//等待键盘输入是一个数字0~1否则就一直等待用户输入
	if(confirm==1)
	{
		head=DeleteNode(head,t);
		return head;
	}
	else
		return head;				
}

//修改字典信息函数
STNODE * Modifydicinfo(STNODE *head)
{
	STNODE *tmp = NULL;
	char ch;
	tmp = findformodify(head);
	if(tmp==NULL)
		return head;
	int confirm = 0;
	printf("请输入confirm的值 1:表示确认修改 0:表示不修改!!! \n");
	confirm=inputdigit01(ch);
	if(confirm == 1)
	{
		printf("请输入缩写的字符编号：");
		scanf("%d",&tmp->diction.ID);
		printf("请输入缩写的字符：");
		scanf("%s",tmp->diction.simpname);
		fflush(stdin);
		printf("请输入全称：");
		scanf("%s",tmp->diction.wholename);
		fflush(stdin);
		printf("请输入中文解释：");
		scanf("%s",tmp->diction.chinesename);
		fflush(stdin);
		return head;
	}
	else
		return head;	
}

//按名字或编号查找的函数
void searchnameorID(STNODE *head)
{
    STNODE *q=NULL;
    char word[30];
    char ch;
	int choice,id;
    printf("请输入choice的值 1：按单词名查找  2：按编号查找\n");
    choice=inputdigit12(ch);//等待键盘输入是一个数字1~2否则就一直等待用户输入
    switch(choice)
    {
    	case 1:
    		printf("请输入缩写名:");
			scanf("%s",word);
    		q=findname(head,word);
    		rethome();
    		break;
		case 2:
			printf("请输入编号:");
			scanf("%d",&id);
			q=findID(head,id);
			rethome();
    		break;
    }
}

//读文件并且打印数据的函数
void showdicinfo(STNODE *head)
{
    struct dictionary dic;
    STNODE *p=head->next;
    if(p==NULL)
    {
    	printf("\t字典中的信息为空,请先添加信息 !!!\n");
    }
    printf("\t\t\t全文信息如下"); 
    printf("\n\t====================================================================================================\n");
    printf("\t%-8s%-8s%-60s%-6s%-30s\n","编号","  简称","    全"  ,  "称","中文翻译");
    while(p!=NULL)//读取数据并打印
    {
		printf("\t%-8d%-8s%-60s%-30s \n",
                p->diction.ID,p->diction.simpname,p->diction.wholename,p->diction.chinesename);         
       p=p->next;
    }        
    printf("\t====================================================================================================\n");
    return;
}


//退出前保存操作
void confirmsave(STNODE *head)
{
	int confirm=0;
	char ch;
	printf("请输入confirm的值,1:表示确认保存 0:表示不保存 !\n");
	confirm=inputdigit01(ch);
	if(confirm == 1)
	{
		save(head);
		printf("信息保存成功!\n");
		printf("press any key to exit...!!\n");
		while(getchar() == '\n');
		printf("\n已安全退出系统,谢谢使用!!\n");
		exit(0);
	}
	else
	{
		printf("\n已安全退出系统,谢谢使用!!\n");
		exit(0);
		
	}
}



