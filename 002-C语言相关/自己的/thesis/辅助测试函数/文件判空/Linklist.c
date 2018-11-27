#include"Linklist.h"
//销毁链表---砍头法
void DestroyLinklist(STNODE *head)
{
     STNODE *q=head->next;
     while(q!=NULL)
     {
       head->next=q->next;
       free(q);
       q=head->next;
     } 
}

//登录判断
PERSONINFO loginlist(PERSONINFO user)
{
    int i=0,j=0;
    STNODE *p = &stPersonHead;
    while(p->next != NULL)
    {
    	if(0 == strcmp(p->next->person.sName,user.sName)) 
    	{  printf("%s\n",user.sName);
                user = p->next->person;
		return user;
    	}
    	p = p->next;
   }
   return user;
}

//保存函数
void save(STNODE head,FILE *file)
{
    while(head.next!=NULL)  //因为是以w的形式打开的文件，所以不论是否修改，都要重写文件
    {
         fwrite(&head.next->person,sizeof(struct PERSONINFO),1,file);
         head.next=head.next->next;
    }
}

//读文件并且打印数据的函数
void readinfo(char filename[25])
{
    PERSONINFO people;
    FILE *file=NULL;
    file=fopen(filename,"rt");
    if(file==NULL)
    {
        printf("打开文件%s出错！\n",filename);
        return;
    }
    rewind(file);
    fread(&people,sizeof(struct PERSONINFO),1,file);
    printf("\t\t\t当前人员信息如下"); 
    printf("\n\t===================================================================\n");
    printf("\t编号     姓 名  性 别     职    称  等 级     电 话   工资     上级\n");
    while(!feof(file))
    {//读取数据并打印
	printf("\t%-8d %-5s     %-8s %-8s     %-8s %-8s%-8d  %-5s\n",
                people.sID,people.sName,people.sex,people.sPostion,
                people.Level,people.sTelPhone,people.salary,people.shangji);         
        fread(&people,sizeof(struct PERSONINFO),1,file);
    }        
    printf("\t===================================================================\n");
    fclose(file);
    file=NULL; //printf("2222\n");
    return;
}

//读文件取出当前文件中最大的ID编号
int readfileID(char filename[25])
{
    PERSONINFO people;
    int ManagerID;
    int filepos=0;
    FILE *file=NULL;
    file=fopen(filename,"rt");
    if(file==NULL)
    {
        printf("打开文件%s出错！\n",filename);
        return 0;
    }
    fseek(file,0,SEEK_END);
    filepos=ftell(file);//报告文件距离文件开头的位移量，如果为0，则表示文件为空
    if(filepos==0)
    {
        return 1;
    }
    else
    {
        fseek(file,-sizeof(struct PERSONINFO),SEEK_END);//放在文件末尾之前的一个结构体处
        fread(&people,sizeof(struct PERSONINFO),1,file);
        ManagerID=people.sID+1;
        printf("%d\n",ManagerID);
        fclose(file);
        file=NULL;
        return ManagerID;
    }
}

//写文件函数
void writeperson(char filename[30],PERSONINFO people)
{
    FILE *file=NULL;
    file=fopen(filename,"at"); //是filename，不能加上“”，加双引号就是字符串了
    if(file!=NULL)
    {   
        printf("\n==================================================\n");
        if(strcmp(filename,"Managerinfo.txt")==0)
        {   
            people.sID=readfileID("Managerinfo.txt");
        }
        if(strcmp(filename,"SaleManagerinfo.txt")==0)
        {
            people.sID=readfileID("SaleManagerinfo.txt");
        }
        if(strcmp(filename,"skillpersoninfo.txt")==0)
        {
            people.sID=readfileID("skillpersoninfo.txt");
        }
        if(strcmp(filename,"salepersoninfo.txt")==0)
        {
            people.sID=readfileID("salepersoninfo.txt");
        }
        printf("\t请输入人员姓名:");
        scanf("%s",people.sName);
        printf("\t请输入人员性别:");
        scanf("%s",people.sex);
        printf("\t请输入人员职称:");
        scanf("%s",people.sPostion);
        printf("\t请输入人员等级:");
        scanf("%s",people.Level);
        printf("\t请输入人员电话:");
        scanf("%s",people.sTelPhone);
        printf("\t请输入人员工资:");
        scanf("%d",&people.salary);
        printf("\t请输入人员上级:");
        scanf("%s",people.shangji);
        printf("==================================================\n");
        fwrite(&people,sizeof(struct PERSONINFO),1,file);
        fclose(file);
        file=NULL; 
    }
    else
    {
        printf("打开文件%s出错！\n",filename);
    }
}


//读文件到链表的子函数
void readfiletolist(PERSONINFO people,FILE *file)
{
    if(file==NULL)
    {
        printf("打开文件出错！\n");
        return;
    }
    else
    {
        while((fread(&people,sizeof(struct PERSONINFO),1,file))==1)//利用尾插法将文件中读取的信息临时存储在链表中
        {
            STNODE *p=malloc(sizeof(struct _STNODE));//1-1创建一个新结点p
            if(stPersonHead.next==NULL)
            {
                stPersonHead.next=p;
                p->next=NULL;
                p->person=people;
            }
            else
            {
                STNODE *tmp=&stPersonHead;
                while(tmp->next!=NULL)  //将指针移动到链表的尾部，即最后一个元素的地方
                    tmp=tmp->next;
                tmp->next=p;
                p->next=NULL;
                p->person=people;
            }
        }//end of while   
    }// end of else
}

//把文件读到链表进行修改操作
void readfiletolinklist(char filename[25])
{
    PERSONINFO people;
    FILE *file=NULL;
    file=fopen(filename,"rt");
    readfiletolist(people,file);//读文件到链表的子函数的调用
    fclose(file);
    file=NULL;
    int found=0;
    int confirm=0;
    char Modifypeoplename[20];
    STNODE *pNode=NULL;
    STNODE head=stPersonHead;  //要先保存好头结点，因为下面的操作将会使得头结点的下一个往后移
    file=fopen(filename,"wt");//为下一步修改信息之后重写到文件中做好准备
    printf("请输入您想修改的人员名：");
    scanf("%s",Modifypeoplename);
    while(stPersonHead.next!=NULL)
    {
         if(strcmp(stPersonHead.next->person.sName,Modifypeoplename)==0)
         {
             found=1;
             pNode=stPersonHead.next; //保存要修改的结点
             break;
         }
         stPersonHead.next=stPersonHead.next->next;
    }
    if(found==1)
    {
        printf("您想要修改的人员信息如下\n");
        printf("\t编号     姓 名  性 别     职    称  等 级     电 话   工资   上级\n");
        printf("\t%-8d %-5s     %-8s %-8s     %-8s %-8s %-8d %-8s\n",
                pNode->person.sID,pNode->person.sName, pNode->person.sex,pNode->person.sPostion,
                pNode->person.Level,pNode->person.sTelPhone,pNode->person.salary,pNode->person.shangji);
        printf("\n确定要修改吗？1：表示确定修改    0：表示取消修改:   ");
        scanf("%d",&confirm);
        if(confirm==1)
          {
               printf("==========请修改人员信息:=========\n");
               printf("=================================\n");
               printf("\t请输入人员编号:");
               scanf("%d",&pNode->person.sID);
               printf("\t请输入人员姓名:");
               scanf("%s",pNode->person.sName);
               printf("\t请输入人员性别:");
               scanf("%s",pNode->person.sex);
               printf("\t请输入人员职称:");
               scanf("%s",pNode->person.sPostion);
               printf("\t请输入人员等级:");
               scanf("%s",pNode->person.Level);
               printf("\t请输入人员电话:");
               scanf("%s",pNode->person.sTelPhone);
               printf("\t请输入人员工资:");
               scanf("%d",&pNode->person.salary);
               printf("\t请输入人员上级:");
               scanf("%s",pNode->person.shangji);
               printf("=================================\n");
               save(head,file);
               printf("信息已保存成功！！\n");
          }
          else
          {    
               save(head,file);
          }
                       
    }
    if(found==0)
    {
         printf("无此人员的信息！！！\n");//因为是以w的形式打开的文件，所以不论是否修改，
         save(head,file);//有没有找到这条记录，都要重写文件，否则内容都会被清空的
    } 
    fclose(file);
    file=NULL;
    DestroyLinklist(&stPersonHead);//销毁链表
}

//释放结点即删除的的子函数
STNODE *deletename(STNODE *head,char personname[30])
{   
    STNODE *p1,*p2;
    FILE *fp;
    fp=fopen("Deletepersoninfo.txt","at");
    if(fp==NULL)
        printf("打开文件Deletepersoninfo.txt错误!\n");
    int found=0,confirm;
    //要删除的为头结点的下一个时
    if(head->next==NULL)
    {
        printf("链表内容为空！！\n");
        return NULL;
    }
    p1=head;//p1是p2的上一个结点
    p2=head->next;
    while(p2!=NULL)
    {
        if(strcmp(p2->person.sName,personname)==0)
        {   
            found=1;
            p1->next=p2->next;
            printf("您要删除的人员信息如下\n");
            print(p2);
            printf("\n确定要删除吗？1：表示确定删除    0：表示取消删除:   ");
            scanf("%d",&confirm);
            if(confirm==1)
            {
                fwrite(&p2->person,sizeof(struct PERSONINFO),1,fp);
                free(p2);
                printf("删除成功！！删除人员已经保存在Deletepersoninfo.txt文件中了\n");
                fclose(fp);
                fp=NULL;p2=NULL;
                return head;
            }
            else
                return head;
          }
          else
              p1=p2;//p1后移一个结点
    p2=p1->next;//p2指向p1的下一个结点
    }
    if(found==0)
     //  printf("没有是此名字的人员信息!\n");
    return head;        
}

//释放结点即删除的的子函数
STNODE *deletenID(STNODE *head,int personID)
{   
    STNODE *p1,*p2;
    FILE *fp;
    fp=fopen("Deletepersoninfo.txt","at");
    if(fp==NULL)
        printf("打开文件Deletepersoninfo.txt错误!\n");
    int found=0,confirm=0;
    //要删除的为头结点的下一个时
    if(head->next==NULL)
    {
        printf("链表内容为空！！\n");
        return NULL;
    }
    p1=head;//p1是p2的上一个结点
    p2=head->next;
    while(p2!=NULL)
    {
        if(p2->person.sID==personID)
        {   
            found=1;
            p1->next=p2->next;
            printf("您要删除的人员信息如下\n");
            print(p2);
            printf("\n确定要删除吗？1：表示确定修改    0：表示取消修改:   ");
            scanf("%d",&confirm);
            if(confirm==1)
            {
                fwrite(&p2->person,sizeof(struct PERSONINFO),1,fp);
                free(p2);
                printf("删除成功！！删除人员已经保存在Deletepersoninfo.txt文件中了\n");
                fclose(fp);
                fp=NULL;
                p2=NULL;
                return head;
            }
            else
                return head;
        }
    else
        p1=p2;//p1后移一个结点
    p2=p1->next;//p2指向p1的下一个结点
    }
    if(found==0)
       //printf("无此编号的人员的信息!\n");
    return head;        
}

//把文件读到链表中进行删除操作
void readfiletolinklistfordeletename(char filename[25])
{
    PERSONINFO people;STNODE *head;
    char pname[30];
    FILE *file=NULL;
    file=fopen(filename,"rt");//scanf("%s",szUser);
                      

    readfiletolist(people,file);//读文件到链表的子函数的调用
    fclose(file);
    file=NULL; 
    file=fopen(filename,"wt");
    printf("请输入您想删除的人员名字\n");
    scanf("%s",pname);
    head=&stPersonHead;
    if(deletename(head,pname)==NULL)
    {
        printf("文件内容为空！无法进行删除操作！！\n");
        fclose(file);
        file=NULL; 
        return ;
    }
    else
    {
        head=deletename(head,pname);//删除函数调用
        while(head->next!=NULL)  //因为是以w的形式打开的文件，所以不论是否修改，都要重写文件
        {
            fwrite(&head->next->person,sizeof(struct PERSONINFO),1,file);
            head->next=head->next->next;
        }
        fclose(file);
        file=NULL; 
    }
}

//把文件读到链表中进行删除操作
void readfiletolinklistfordeleteID(char filename[25])
{
    PERSONINFO people;STNODE *head;
    int pID;
    FILE *file=NULL;
    file=fopen(filename,"rt");
    readfiletolist(people,file);//读文件到链表的子函数的调用
    fclose(file);
    file=NULL; 
    file=fopen(filename,"wt");
    printf("请输入您想删除的编号\n");
    scanf("%d",&pID);
    head=&stPersonHead;
    if(deletenID(head,pID)==NULL)
    {
        printf("文件内容为空！无法进行删除操作！！\n");
        fclose(file);
        file=NULL; 
        return ;
    }
    else
    {
        head=deletenID(head,pID);//删除函数调用
        while(head->next!=NULL)  //因为是以w的形式打开的文件，所以不论是否修改，都要重写文件
        {
            fwrite(&head->next->person,sizeof(struct PERSONINFO),1,file);
            head->next=head->next->next;
        }
        fclose(file);
        file=NULL; 
    }
}

int xianshi()
{
STNODE *p = &stPersonHead;
    while(p->next != NULL)
    {
        print(p->next);
	p = p->next;
    }
return 0;
}

//打印内容
void print(STNODE *pNode)
{
    printf("\t编号     姓 名  性 别     职    称  等 级     电 话   工资      上级\n");
    printf("\t%-8d %-5s     %-8s %-8s     %-8s %-8s   %-8d  %-8s\n",
           pNode->person.sID,pNode->person.sName, pNode->person.sex,pNode->person.sPostion,
           pNode->person.Level,pNode->person.sTelPhone,pNode->person.salary,pNode->person.shangji);
}

//按名字或编号查找的子函数
void foundnameorID(PERSONINFO people,int choice,int found,FILE *file)
{   
    int personID;
    char personname[48];
    switch(choice)
        {
         case 1:
              printf("请输入您想查找的人员名：");
              scanf("%s",personname);
              while((fread(&people,sizeof(struct PERSONINFO),1,file))==1)
              {
                  if((strcmp(people.sName,personname))==0)
                  {
                      found=1;
                      break;
                  }  
              }
              break;
         case 2:
              printf("请输入您想查找的人员编号：");
              scanf("%d",&personID);
              while((fread(&people,sizeof(struct PERSONINFO),1,file))==1)
              {
                  if(personID==people.sID)
                  {
                      found=1;
                      break;
                  }  
              }
             break;
        }
        tishi(found,people);
}
//找到或没找到的提示函数
void tishi(int found,PERSONINFO people)
{
    if(found==1)
    {
        printf("您想要查找的人员信息如下\n");
        printf("\t编号     姓 名  性 别     职    称  等 级     电 话   工资     上级\n");
        printf("\t%-8d %-5s     %-8s %-8s     %-8s %-8s  %-8d %-5s \n",
                    people.sID,people.sName, people.sex,people.sPostion,
               people.Level,people.sTelPhone,people.salary,people.shangji); 
    }
    if(found==0&&choice1==1)
    {
        printf("在文件中没有找到此人员的相关纪录！！！\n");
    }
    if(found==0&&choice1==2)
    {
        printf("在文件中没有找到此编号的人员的相关纪录！！！\n");
    }  
}
//按名字或编号查找的函数
void searchnameorID(char filename[25])
{
    PERSONINFO people;
    int found=0,choice;
    FILE *file=NULL;
    file=fopen(filename,"rt");
    if(file==NULL)
    {
        printf("打开文件%s出错！\n",filename);
        return;
    }
    else
    {
        rewind(file);
        printf("请输入choice的值 1：按人名查找  2：按编号查找\n");
        scanf("%d",&choice);
        choice1=choice;
        foundnameorID(people,choice,found,file);//按名字或编号查找的子函数的调用
    }//end of else
    fclose(file);
    file=NULL;
}

//员工工资
void personsalary(char filename[30])
{
    PERSONINFO people;
    STNODE *p;
    FILE *file=NULL;
    file=fopen(filename,"rt");
    readfiletolist(people,file);//读文件到链表的子函数的调用
    fclose(file);
    file=NULL;
    p=stPersonHead.next;
    while(p!=NULL)
    {
        if(strcmp(p->person.Level,"a")==0)
        {
            p->person.salary=employsalary[0];
        }
        if(strcmp(p->person.Level,"b")==0)
        {
            p->person.salary=employsalary[1];
        }
        if(strcmp(p->person.Level,"c")==0)
        {
            p->person.salary=employsalary[2];
        }
        if(strcmp(p->person.Level,"d")==0)
        {
            p->person.salary=employsalary[3];
        }
        p=p->next;
    }
    file=fopen(filename,"wt");
    save(stPersonHead,file);
    printf("员工工资导入成功！\n");
    fclose(file);
    file=NULL;
}

//读文件到链表的汇总信息子函数
void readfiletohuizong(char filename[40])
{
    FILE *file;
    file=fopen(filename,"rt");
    PERSONINFO people;
    if(file==NULL)
    {
        printf("打开文件出错！\n");
        return;
    }
    else
    {
        while((fread(&people,sizeof(struct PERSONINFO),1,file))==1)//利用尾插法将文件中读取的信息临时存储在链表中
        {
            STNODE *p=malloc(sizeof(struct _STNODE));//1-1创建一个新结点p
            if(stPersonHead.next==NULL)
            {
                stPersonHead.next=p;
                p->next=NULL;
                p->person=people;
            }
            else
            {
                STNODE *tmp=&stPersonHead;
                while(tmp->next!=NULL)  //将指针移动到链表的尾部，即最后一个元素的地方
                    tmp=tmp->next;
                tmp->next=p;
                p->next=NULL;
                p->person=people;
            }
        }//end of while   
    }// end of else
}

//读文件到链表的写入文件汇总信息
void readfiletohuizonglist(char filename[40])
{ 
    FILE *file;
    file=fopen(filename,"wt");
    STNODE head=stPersonHead;
    save(head,file);
}

//按等级排序
void sort(char filename[30])
{
    PERSONINFO people;
    FILE *file=NULL;
    file=fopen(filename,"rt");
    readfiletolist(people,file);
    STNODE *head=&stPersonHead;
    STNODE *p=NULL,*p1=NULL,*p2=NULL;
    STNODE *p3=p1;
    printf("按等级排序后的人员信息如下\n");
    printf("\t编号     姓 名  性 别     职    称  等 级     电 话   工资    上级\n");
    for(p1=head->next;p1!=NULL;p1=p1->next)
    {   
        for(p2=p1->next;p2!=NULL;p2=p2->next)
        {
            if(strcmp(p1->person.Level,p2->person.Level)>0)
              {  p3->person=p2->person;p2->person=p1->person;p1->person=p3->person;}
        }
        printf("\t%-8d %-5s     %-8s %-8s     %-8s %-8s  %-8d %-5s \n",
                    p1->person.sID,p1->person.sName, p1->person.sex,p1->person.sPostion,
               p1->person.Level,p1->person.sTelPhone,p1->person.salary,p1->person.shangji);
    }
    return;
}

/*
//显示按等级排序后的
void show()
{
    STNODE *head=sort("Managerinfo.txt");
    STNODE *p=head;
    printf("按等级排序后的人员信息如下\n");
    printf("\t编号     姓 名  性 别     职    称  等 级     电 话   工资   上级\n");
    while(head->next!=NULL)
    {
        printf("\t%-8d %-5s     %-8s %-8s     %-8s %-8s  %-8d %-5s \n",
                    head->next->person.sID,head->next->person.sName, head->next->person.sex,head->next->person.sPostion,
               head->next->person.Level,head->next->person.sTelPhone,head->next->person.salary,head->next->person.shangji); 
        head->next=head->next->next;
    }
}

*/












