#include"data.h"
//读文件取出当前文件中最大的ID编号
int readfileID(STNODE *head)
{
    STNODE *p=head->next;
    int bianhaoID;
    if(p==NULL)
    {
        return 1;
    }
    bianhaoID=p->diction.ID;
    while(p->next!=NULL)
    {	
    	if(p->next->diction.ID>bianhaoID)
    		bianhaoID=p->next->diction.ID;
    	p=p->next;	
    }
    bianhaoID=bianhaoID+1;
    printf("%d\n",bianhaoID);
    return bianhaoID;
 }

//销毁链表---砍头法
void DestroyLinklist(STNODE *head)
{
    STNODE *q=(STNODE *)malloc(sizeof (STNODE));
    q=head->next;
    while(q!=NULL)
    {
    	head->next=q->next;
    	free(q);
    	q=head->next;
     } 
}

//保存函数
void save(STNODE *head)
{
	FILE *file;
	file=fopen("dictionary.txt","w");
	if(file == NULL)
	{
		printf("文件打开错误!!\n");
		return;
	}
    while(head->next!=NULL)  //因为是以w的形式打开的文件，所以不论是否修改，都要重写文件
    {
         fwrite(&(head->next->diction),sizeof(struct dictionary),1,file);
         head->next=head->next->next;
    }
}

//读文件到链表的子函数
STNODE * readfiletolist(char filename[30])
{
	STNODE *head=(STNODE *)malloc(sizeof(struct STNODE));
	head->next==NULL;
	DIC people;
	FILE *file=fopen(filename,"rt");
    if(file==NULL)
    {
        printf("打开文件出错！\n");
        return;
    }
    else
    {
        while((fread(&people,sizeof(DIC),1,file))==1)//利用尾插法将文件中读取的信息临时存储在链表中
        {
            STNODE *p=(STNODE *)malloc(sizeof(struct STNODE));//1-1创建一个新结点p
                STNODE *tmp=head;
                while(tmp->next!=NULL)  //将指针移动到链表的尾部，即最后一个元素的地方
                    tmp=tmp->next;
                tmp->next=p;
                p->next=NULL;
                p->diction=people;
        }//end of while   
    }// end of else
    return head;
}

//释放结点子函数
STNODE * DeleteNode(STNODE *head,STNODE *q)
{
    STNODE *p=head;
    while(p->next!=NULL)
    {
         if(p->next==q)//比较地址,相同则找到了要删除的结点
         {
             STNODE *s=p->next;//保存要删除结点的地址
             p->next=p->next->next;//链接删除节点的前一个结点和后一个结点
             free(s);
             s=NULL;
             return head;
         }
         p=p->next;
    }
    if(p==q)//删除最后一个结点,置最后一个结点为空即可
    {
    	p=NULL;
    }
    return head;
}


//返回主界面函数
void rethome()
{
	printf("\n按任意键回车后返回主界面 !!!\n");
	while(getchar() == '\n');
}

// 等待键盘输入是一个数字1~2否则就一直等待用户输入
int inputdigit12(char ch)
{
	do
	{
		ch=getchar();
	}
	while(!(ch>='1'&&ch<='2'));
	return ch-'0';
}

// 等待键盘输入是一个数字1~2否则就一直等待用户输入
int inputdigit01(char ch)
{
	do
	{
		ch=getchar();
	}
	while(!(ch>='0'&&ch<='1'));
	return ch-'0';
}

//打印信息函数
void print(DIC dic)
{
	printf("\t%-8s%-8s%-60s%-6s%-30s\n","编号","  简称","    全"  ,  "称","中文翻译");
    		printf("\t%-8d%-8s%-60s%-30s \n",
                dic.ID,dic.simpname,dic.wholename,dic.chinesename);  
}

//按缩写名查找并返回地址
STNODE *findname(STNODE *head,char suoxiename[30])
{
    STNODE *p=head->next;
    while(p!=NULL)
    {
    	if(strcmp(suoxiename,p->diction.simpname)==0)
    	{
    		printf("\t\t\t\t\t\t您想要查找的信息如下\n\n");
    		print(p->diction);//打印信息
    		return p;
    	}
    	p=p->next;
    }
    printf("文件中没有缩写是%s的信息!!!\n",suoxiename);
	return NULL;
}

//按编号查找并返回地址
STNODE *findID(STNODE *head,int bianhao)
{
    STNODE *p=head->next;
    while(p!=NULL)
    {
    	if(bianhao==p->diction.ID)
    	{
    		printf("\t\t\t\t\t\t您想要查找的信息如下\n\n");
    		print(p->diction);//打印信息
    		return p;
    	}
    	p=p->next;
    }
    printf("文件中没有编号是%d的信息!!!\n",bianhao);
	return NULL;
}

//按名字或编号查找的函数
STNODE * findfordelete(STNODE *head)
{
    STNODE *q=NULL;
    char word[30];
    char ch;
	int choice,id;
    printf("请输入choice的值 1：按单词名删除  2：按编号删除\n");
    choice=inputdigit12(ch);//等待键盘输入是一个数字1~2否则就一直等待用户输入
    switch(choice)
    {
    	case 1:
    		printf("请输入缩写名:");
			scanf("%s",word);
    		q=findname(head,word);
    		return q;
    		break;
		case 2:
			printf("请输入编号:");
			scanf("%d",&id);
			q=findID(head,id);
			return q;
    		break;
    }
}

//按名字或编号查找的函数
STNODE * findformodify(STNODE *head)
{
    STNODE *q=NULL;
    char word[30];
    char ch;
	int choice,id;
    printf("请输入choice的值 1：按单词名修改  2：按编号修改\n");
    choice=inputdigit12(ch);//等待键盘输入是一个数字1~2否则就一直等待用户输入
    switch(choice)
    {
    	case 1:
    		printf("请输入缩写名:");
			scanf("%s",word);
    		q=findname(head,word);
    		return q;
    		break;
		case 2:
			printf("请输入编号:");
			scanf("%d",&id);
			q=findID(head,id);
			return q;
    		break;
    }
}
