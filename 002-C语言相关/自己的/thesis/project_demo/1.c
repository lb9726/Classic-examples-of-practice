#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct wokers				//定义一个woker的结构体
{
char num[10];				//职工号
char name[15];				//职工姓名
char sex[15];				//职工性别
char birthday[15];          //职工出生年月
char  degree[10];           //职工学历
char position[10];          //职工职位
char salary[10];            //职工工资
};


typedef struct node
{
struct wokers data;
struct node *next;			//建立一个链表。
}Node;

void Add(Node *woker)		//添加记录
{
Node *p,*r,*s;     
char n[10];				    //先用于输入职工号,也用于判断是否跳出循环
r=woker;
s=woker->next;              //使s为第一个有用的结点
while(r->next!=NULL)        //这个循环的作用是使r为最后一个有用的结点
r=r->next;                  //将指针置于最末尾
while(1)
{ 
    printf(">>>>>>>>>>提示:输入0则返回主菜单!\n");
    printf("\n请你输入职工号:");      
    scanf("%s",n);                
    if(strcmp(n,"0")==0)  break;                     
    p=(Node *)malloc(sizeof(Node));   //申请空间
    strcpy(p->data.num,n);
    printf("\n请输入姓名:");
    scanf("%s",p->data.name);          
    printf("\n请输入性别:");
    scanf("%s",p->data.sex);
    printf("\n请输入出生年月:");
    scanf("%s",&p->data.birthday);
    printf("\n请输入学历:");
    scanf("%s",&p->data.degree);
    printf("\n请输入职位:");  
    scanf("%s",&p->data.position);
    printf("\n请输入工资:");
    scanf("%s",&p->data.salary);
    printf(">>>>>>>>>>提示:已经完成一条记录的添加。\n");
    p->next=NULL;
    r->next=p;       //这一步是必需的,将p与先前的链表连起来构成一条新链表
    r=p;             //也是必需的.将r 又重设为新链的最后一个有用结点 
}
}


void change(Node *woker)		//修改职工信息函数
{
Node *p;
char find[20];
if(!woker->next)
{
    printf("\n>>>>>>>>>>提示:没有资料可以修改!\n");
    return;
}
printf("请输入要修改的职工号:");   
scanf("%s",find); 
    p=woker->next;   
     while(p!=NULL)   
     {
      if(strcmp(p->data.num,find)==0)     //如果找到的话返回的是符合要求
       break; 
       p=p->next;
     }
     if(p)						
     {
       int x;
       while(1)
       {
        printf("完成修改请输入0否则输入任意数再进行修改:");
        scanf("%d",&x);
        if(x==0)
        {break;} 
           printf("请输入新职工号(原来是 %s ):",p->data.num);
           scanf("%s",p->data.num);
           printf("请输入新职工姓名(原来是 %s ):",p->data.name);
           scanf("%s",p->data.name);
           printf("请输入新职工性别(原来是 %s ):",p->data.sex);
           scanf("%s",p->data.sex);  
           printf("请输入新出生年月(原来是 %s ):",p->data.birthday);
           scanf("%s",p->data.birthday);  
           printf("请输入新职工学历(原来是 %s ):",p->data.degree);
           scanf("%s",p->data.degree); 
           printf("请输入新职工职位(原来是 %s ):",p->data.position);
           scanf("%s",p->data.position); 
           printf("请输入新职工工资(原来是 %s ):",p->data.salary);
           scanf("%s",p->data.salary); 
           printf("\n>>>>>>>>>>提示:该项记录资料已经成功修改!\n");
    }
    }
    else    printf("\n>>>>>>>>>>提示:你要修改的信息不存在!\n");
}      
void Disp(Node *woker)					//输出职工信息
{
Node *p;
p=woker->next;
if(!p)
{
    printf("\n>>>>>>>>>>提示:没有记录可以显示!\n");
    return;
}
    printf("\t\t\t\t显示结果\n");     
    printf("职工号   职工姓名   职工性别   职工生日   职工学历   职工职位   职工工资\n");       
while(p)
{
    printf("\n%-13s%-11s%-7s%-10s%-13s%-10s%-5s\n",p->data.num,p->data.name,p->data.sex,p->data.birthday,p->data.degree,p->data.position,p->data.salary);
    p=p->next;
}
}
void Tongji(Node *woker)				//查找统计函数
{
Node *p;
int sel;int flag2=0,ha=0;
char find[20];  
p=woker->next;
   
if(!woker->next)						//若链表为空
{
    printf("\n>>>>>>>>>>提示:没有资料可以统计分类!\n");
    return;
}
printf(">>>>>>>>>>提示:\n=====>0退出\n=====>1按职工号统计\n=====>2按职工姓名名称统计\n");
scanf("%d",&sel);
if(sel==1)
{
    printf("\n输入你要统计分类的职工号:");
	scanf("%s",find);
    while(p)
    {  
     if(strcmp(p->data.num,find)==0)
     {
      flag2++;
     } 
     if(flag2==1&&ha!=flag2)
     { printf("职工号   职工姓名   职工性别   职工生日   职工学历   职工职位   职工工资\n");
       printf("\n%-13s%-11s%-7s%-10s%-13s%-10s%-5s\n",p->data.num,p->data.name,p->data.sex,p->data.birthday,p->data.degree,p->data.position,p->data.salary);
       ha=flag2;
     }
     else if(flag2>ha){printf("\n%-13s%-11s%-7s%-10s%-13s%-10s%-5s\n",p->data.num,p->data.name,p->data.sex,p->data.birthday,p->data.degree,p->data.position,p->data.salary);ha=flag2;}
     p=p->next;
    }
    if(flag2)
    {
     printf("\n*************************按设备号%s统计分类的有%d条记录:*************************\n\n",find,flag2);
    }
    else {printf("\n按职工号%s统计的结果为0个\n\n",find);}
}
else if(sel==2)
{
     printf("\n输入你要统计分类的职工姓名:");
           scanf("%s",find);
    while(p)
    {  
     if(strcmp(p->data.name,find)==0)
     {
      flag2++;
     }   
     if(flag2==1&&ha!=flag2)
     { printf("职工号   职工姓名   职工性别   职工生日   职工学历   职工职位   职工工资\n");
       printf("\n%-13s%-11s%-7s%-10s%-13s%-10s%-5s\n",p->data.num,p->data.name,p->data.sex,p->data.birthday,p->data.degree,p->data.position,p->data.salary);
      ha=flag2;
     }
     else if(flag2>ha){printf("\n%-13s%-11s%-7s%-10s%-13s%-10s%-5s\n",p->data.num,p->data.name,p->data.sex,p->data.birthday,p->data.degree,p->data.position,p->data.salary);ha=flag2;}
     p=p->next;
    }
    if(flag2)
    {
     printf("\n\n\n共查找到%d条记录:\n\n",flag2);
    }
    else {printf("\n按职工姓名%s统计分类的结果为0个\n\n",find);}
}
else if(sel==0) return;
}


void load(Node *woker)
{Node *p,*q;
FILE *fp;												//指向文件的指针
int recordNum;											// 统计记录数

if((fp = fopen("职工管理系统.txt", "rb")) == NULL)		//打开文件
{
printf("can not open file\n");							//不能打开

}
p=woker;
recordNum = 0;
while(!feof(fp))
{q=(Node*)malloc(sizeof(Node)); 
fscanf(fp, "%s %s %s %s %s %s %s",p->data.num,p->data.name,p->data.sex,p->data.birthday,p->data.degree,p->data.position,p->data.salary);/*从文件读入记录*/
p->next=q;
q->next=NULL;
p=q;
recordNum++;
}
fclose(fp);
printf("文件里共有%d条记录:\n",recordNum);
}


void save(Node *woker)									//将职工信息保存到文件
{
int n;
Node *p;
FILE *fp;												 //指向文件的指针
printf("需要保存到文件吗?（1—保存，0—不保存）");
	scanf("%d",&n);
	if(n==1)
	{
	if(woker->next==NULL)
		printf("无记录");
	else p=woker->next;
	if((fp = fopen("职工管理系统.txt", "wb")) == NULL) //打开文件，并判断打开是否正常
		printf("can not open file\n");					// 打开文件出错
	while(p!=NULL)
{
fprintf(fp,"%s %s %s %s %s %s %s",&p->data.num,&p->data.name,&p->data.sex,&p->data.birthday,&p->data.degree,&p->data.position,&p->data.salary);
p=p->next;
}
fclose(fp);												//关闭文件
}
}
void dismiss(Node *woker)								//删除职工信息函数
{Node *p,*r,*s;
char find[10];
if(!woker->next) 
{ 
printf("\n>>>>>>>>>>提示:没有资料可以显示!\n"); 
return; 
}
printf("\n>>>>>>>>>>提示:请输入您要删除的职工号!\n");
scanf("%s",find);
p=woker->next;
while(p!=NULL) 
{ 
if(strcmp(p->data.num,find)==0)							//如果找到的话返回的是符合要求 
break; 
p=p->next; 
}
if(!p)
printf("\n>>>>>>>>>>提示:找不到您想删除的职工号!\n");
else
{r=woker;
while(r->next!=p)
r=r->next;
s=r->next;
r->next=r->next->next;
}
}


void main()
{
Node *woker;
FILE *fp;
int flag;
Node *p,*q;
	system("color 0F");
    woker=(Node*)malloc(sizeof(Node));
    woker->next=NULL;
    p=woker;
    while(1)
    { printf("\t\t\t\t职工信息管理系统\n");
     printf("\n\n  ==================================选单======================================\n");
     printf("\n\t1、添加记录\n");
     printf("\n\t2、修改记录\n");
     printf("\n\t3、浏览记录\n");
     printf("\n\t4、分类查找记录\n");
     printf("\n\t5、删除记录\n");
     printf("\n\t6、从文件读取记录\n");
     printf("\n\t0、退出\n");
     printf("\n\n输入序号:");
     scanf("%d",&flag);
     switch(flag)
     {
      case 0:     printf("\n>>>>>>>>>>提示:已经退出系统,ByeBye!<<<<<<<<<<\n");break;
      case 1:     Add(woker);save(woker);break;			//增加记录
      case 2:     change(woker);    break;				//修改记录
      case 3:     Disp(woker);      break;				//显示记录信息
      case 4:     Tongji(woker);    break;				//查找记录
      case 5:     dismiss(woker);	break;				//删除记录
      case 6:     load(woker);		break;				//读取记录
      default:    printf("\n>>>>>>>>>>提示:输入错误!\n"); break;
     }system("cls");
    }
}

