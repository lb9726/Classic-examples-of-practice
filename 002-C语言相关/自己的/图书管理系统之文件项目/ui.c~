//包含对应的.h文件
//函数的定义

#include "ui.h"

int LoginUI()
{
    //界面绘制
    //sz:char[]
    system("clear");
    char szUser[40]={'\0'};
    char szPass[40]={'\0'};
    printf("\t网购图书管理系统\n");
    printf("\t");
    printf("用户名:");
    scanf("%s",szUser);
    printf("\t密码:");
    
    scanf("%s",szPass);
    if(strcmp(szUser,"admin")==0&&strcmp(szPass,"123456")==0)
	return 1;
    
    return 0;

}

//主界面
int  MainUI()
{
    //i:int
    int iChoice = 0;
    system("clear");
    printf("================================\n");
    printf("\t1.添加图书信息\n");
    printf("\n");
    printf("\t2.删除图书信息\n");
    printf("\n");
    printf("\t3.查看图书信息\n");
    printf("\n");
    printf("\t4.更改图书信息\n");
    printf("\n");
    printf("\t5.添加会员信息\n");
    printf("\n");
    printf("\t6.查看会员信息\n");
    printf("\n");
    printf("\t7.删除会员信息\n");
    printf("\n");
    printf("\t8.更改会员信息\n");
    printf("\n");
    printf("\t0.退出\n");
    printf("================================\n");
    printf("请输入功能编号1~8,0 表示退出:");
    scanf("%d",&iChoice);
    
    return iChoice;

}

int AddBookUI()
{
    fp=NULL;
    system("clear");
    printf("================================\n");
    printf("\t请输入图书名称:");
    scanf("%s",stBookInfo.szName);
    printf("\t请输入图书作者:");
    scanf("%s",stBookInfo.szAuthor);
    printf("\t请输入图书出版社:");
    scanf("%s",stBookInfo.szPress);
    printf("\t请输入图书定价:");
    scanf("%d",&stBookInfo.dPrice);
    printf("\t请输入库存量:");
    scanf("%d",&stBookInfo.iCount);
    printf("================================\n");
    fp=fopen("bookinf.txt","at");//追加的方式添加了书本信息
    fwrite(&stBookInfo,sizeof(struct _STBOOKINFO),1,fp);
    fclose(fp);
    fp=NULL; 
 
}


int showBookUI()
{
    system("clear");
    fp=fopen("bookinf.txt","r");
    rewind(fp);
    fread(&stBookInfo,sizeof(struct _STBOOKINFO),1,fp);
    printf("\t\t当前图书信息\n");
    printf("===========================================\n");
    printf("名  称  作  者  出版社   定  价  库存量\n");
    while(!feof(fp))
    {//读取数据并打印
	printf("%-8s %-8s %-8s %-8d %-8d\n",
                stBookInfo.szName,stBookInfo.szAuthor,
                stBookInfo.szPress,stBookInfo.dPrice,stBookInfo.iCount);         
        fread(&stBookInfo,sizeof(struct _STBOOKINFO),1,fp);
    }
    printf("===========================================\n");
    fclose(fp);
    fp=NULL; 
    printf("Press Any Key to continue...\n");
    while(getchar() == '\n');//这样就不会直接跳到功能列表页面，否则就像没有输入或输入无效的感觉
    return 1;
}

//删除图书信息
void delete_bookinfo() 
{
     struct _STBOOKINFO Info[100];
     struct _STBOOKINFO temp_str;
     struct _STBOOKINFO delete_str;
     int t=0;int s=0;
     char reply='y';
     char found='y';
     int confirm=1;
     char deleteName[20];
     FILE *fp2;
     while(reply=='y')
     {
          system("clear");
          fp2=fopen("bookinf.txt","r");
          if(fp2!=NULL)
          {    t=0;
               found='n';
               printf("\n请输入要删除的书名:\n");
               scanf("%s",deleteName);
               while((fread(&temp_str,sizeof(struct _STBOOKINFO),1,fp2))==1)
               {
                    if((strcmp(deleteName,temp_str.szName))==0)
                    {  
                         found='y'; 
                         delete_str=temp_str;//查找要删除的纪录,如果找到了，就把temp_str赋给delete_str
                    }
                    else
                    {
                          Info[t]=temp_str;t++;//将不需要删除的纪录保存起来,用t来纪录纪录的总的条数，
                                               //如果没有找到t的值就是原来的值
                    }
               }
          }
          else
          {
               printf("\n打开文件是出现错误，按任意键返回……\n");
               getchar();
               return;
          }
          fclose(fp2);
          if(found=='y') //找到了需要删除的纪录
          {    
               printf("找到了您需要删除的纪录的信息如下\n");
               printf("\n=================================\n");
               printf("\n书名：%s\n",delete_str.szName);
               printf("\n作者：%s\n",delete_str.szAuthor);
               printf("\n出版社：%s\n",delete_str.szPress);
               printf("\n定价：%d\n",delete_str.dPrice);
               printf("\n库存量：%d\n",delete_str.iCount);
               printf("\n=================================\n");
          }
          else
          {
               printf("\n无此书的信息，按任意键返回……\n");
               getchar();
               break;
          }
          printf("\n图书的纪录条数为：t=%d\n",t);
          printf("\n确定要删除吗？1：表示确定删除 0：表示取消删除");
          scanf("%d",&confirm);
          char ti=getchar();
          if(confirm==1)
          { 
               fp2=fopen("bookinf.txt","w");
               if(fp2!=NULL)
               {
                    for(s=0;s<t;s++)
                    {
                        fwrite(&Info[s],sizeof(struct _STBOOKINFO),1,fp2);
                    }
                    printf("\n此纪录已删除!!!\n");
               }
               else
               {
                    printf("\n打开文件是出现错误，按任意键返回……\n");
                    getchar();
                    return; 
               }
               fclose(fp2);
          }
         printf("\n要继续吗？（y/n）：");
         scanf("%c",&reply);
     } 
      printf("\n按任意键返回主菜单……\n");
      getchar();
}

//更改图书信息
void ModifyBook()
{
     struct _STBOOKINFO Info[100];
     struct _STBOOKINFO temp_str;
     char reply='y';
     char found='y';
     int confirm=1;
     char ModifybookName[20];
     FILE *fp2;
     while(reply=='y')
     {
          found='n';
          fp2=fopen("bookinf.txt","r+w");
          if(fp2!=NULL)
          {
               printf("\n请输入要修改的书名:\n");
               scanf("%s",ModifybookName);
               while((fread(&temp_str,sizeof(struct _STBOOKINFO),1,fp2))==1)
               {
                    if((strcmp(ModifybookName,temp_str.szName))==0)
                    {  
                         found='y'; 
                         break;
                    }
               }
          }
          else
          {
               printf("\n打开文件是出现错误，按任意键返回……\n");
               getchar();
               return;
          }
          if(found=='y') //找到了需要修改的纪录
          {    
               printf("找到了您需要修改的纪录的信息如下\n");
               printf("\n=================================\n");
               printf("\n书名：%s\n",temp_str.szName);
               printf("\n作者：%s\n",temp_str.szAuthor);
               printf("\n出版社：%s\n",temp_str.szPress);
               printf("\n定价：%d\n",temp_str.dPrice);
               printf("\n库存量：%d\n",temp_str.iCount);
               printf("\n=================================\n");
               printf("==========请修改图书信息:=========\n");
               printf("================================\n");
               printf("请输入图书名称:");
               scanf("%s",temp_str.szName);
               printf("请输入图书作者:");
               scanf("%s",temp_str.szAuthor);
               printf("请输入图书出版社:");
               scanf("%s",temp_str.szPress);
               printf("请输入图书定价:");
               scanf("%d",&temp_str.dPrice);
               printf("请输入库存量:");
               scanf("%d",&temp_str.iCount);
               printf("================================\n");
               
          }
          else
          {
               printf("\n无此书的信息，按任意键返回……\n");
               getchar();
               break;
          }
          printf("\n确定要修改吗？1：表示确定修改 0：表示取消修改");
          scanf("%d",&confirm);
          char ti=getchar();
          if(confirm==1)
          { 
           fseek(fp2,-sizeof(struct _STBOOKINFO),1);
           fwrite(&temp_str,sizeof(struct _STBOOKINFO),1,fp2);
           printf("此图书的信息已经修改成功！！！");    
          }
         fclose(fp2);
         printf("\n要继续吗？（y/n）：");
         scanf("%c",&reply);
     } 
      printf("\n按任意键返回主菜单……\n");
      getchar();
     
    return ;
}

//添加会员
int AddUser()
{
    fp=NULL;
    system("clear");
    printf("\t请输入会员ID:");
    scanf("%d",&UserInfo.ID);
    printf("\t请输入用户名:");
    scanf("%s",UserInfo.sName);
    printf("\t请设置密码:");
    scanf("%s",UserInfo.sPasswd);
    printf("\t请输入会员级别:");
    scanf("%d",&UserInfo.Level);
    printf("\t请输入用户电话:");
    scanf("%s",UserInfo.sTelPhone);
    fp=fopen("userinf.txt","at");
    fwrite(&UserInfo,sizeof(struct _USERINFO),1,fp);
    fclose(fp);
    fp=NULL; 
}

//查看用户信息 
int ShowUser()
{
    system("clear");
    fp=fopen("userinf.txt","r");
    fseek(fp,0L,SEEK_SET);
    fread(&UserInfo,sizeof(struct _USERINFO),1,fp);
    printf("\t会员信息如下:\n");
    printf("ID      用户名    密 码        级 别    电  话 \n");
    while(!feof(fp))
    {//读取数据并打印
	printf("%-8d %-8s %-8s \t%-d \t%-8s \n",
                UserInfo.ID,UserInfo.sName,
                UserInfo.sPasswd,UserInfo.Level,
                UserInfo.sTelPhone);         
    fread(&UserInfo,sizeof(struct _USERINFO),1,fp);
    }
    fclose(fp);
    fp=NULL; 
    printf("Press Any Key to continue...\n");
    while(getchar() == '\n');
    return 1;
}

//删除会员信息
void DeleteUser()
{
  
     struct _USERINFO Info[100];
     struct _USERINFO temp_str;
     struct _USERINFO delete_str;
     int t=0;int s=0;
     char reply='y';
     int found=1;
     int confirm=1;
     char deleteUserName[20];
     int deleteUserID=0;
     FILE *fp2;
     while(reply=='y')
     {
          system("clear");
          fp2=fopen("userinf.txt","r");
          if(fp2!=NULL)
          {    t=0;
               found=0;
               printf("\n请输入要删除的会员名:\n");
               scanf("%d",&deleteUserID);
               while((fread(&temp_str,sizeof(struct _USERINFO),1,fp2))==1)
               {
                    if(deleteUserID==temp_str.ID)
                    {  
                         found=1; 
                         delete_str=temp_str;//查找要删除的纪录,如果找到了，就把temp_str赋给delete_str
                         printf("\n会员的纪录条数为：t=%d\n",t);
                    }
                    else
                    {
                          Info[t]=temp_str;t++;//将不需要删除的纪录保存起来,用t来纪录纪录的总的条数                                  
                    }
               }
          }   //end if
          else
          {
               printf("\n打开文件是出现错误，按任意键返回……\n");
               getchar();
               return;
          }
          fclose(fp2);
          if(found==1) //找到了需要删除的纪录
          {    
               printf("找到了您需要删除的会员纪录的信息如下\n");
               printf("\n=================================\n");
               printf("\n会员号：%d\n",delete_str.ID);
               printf("\n会员名：%s\n",delete_str.sName);
               printf("\n密码：%s\n",delete_str.sPasswd);
               printf("\n等级：%d\n",delete_str.Level);
               printf("\n联系电话：%s\n",delete_str.sTelPhone);
               printf("\n=================================\n");
          }
          else
          {
               printf("\n无此会员的信息，按任意键返回……\n");
               getchar();
               break;
          }
          printf("\n会员的纪录条数为：t=%d\n",t);
          printf("\n确定要删除吗？1：表示确定删除 0：表示取消删除  ");
          scanf("%d",&confirm);
          char ti=getchar();
          if(confirm==1)
          { 
               fp2=fopen("userinf.txt","w");
               if(fp2!=NULL)
               {
                    for(s=0;s<t;s++)
                    {
                        fwrite(&Info[s],sizeof(struct _USERINFO),1,fp2);
                    }
                    printf("\n此会员纪录已删除!!!\n");
               }
               else
               {
                    printf("\n打开文件是出现错误，按任意键返回……\n");
                    getchar();
                    return; 
               }
               fclose(fp2);
          }
         printf("\n要继续吗？（y/n）：");
         scanf("%c",&reply);
   
     printf("\n按任意键返回主菜单……\n");
     getchar();
}
    return ;
}


//更改会员信息
void ModifyUser()
{
     struct _USERINFO Info[100];
     struct _USERINFO temp_str;
     char reply='y';
     char found='y';
     int confirm=1;
     char ModifyUserName[20];
     FILE *fp2;
     while(reply=='y')
     {
          found='n';
          fp2=fopen("userinf.txt","r+w");
          if(fp2!=NULL)
          {
               printf("\n请输入要修改的用户名:\n");
               scanf("%s",ModifyUserName);
               while((fread(&temp_str,sizeof(struct _USERINFO),1,fp2))==1)
               {
                    if((strcmp(ModifyUserName,temp_str.sName))==0)
                    {  
                         found='y'; 
                         break;
                    }
               }
          }
          else
          {
               printf("\n打开文件是出现错误，按任意键返回……\n");
               getchar();
               return;
          }
          if(found=='y') //找到了需要修改的纪录
          {    
               printf("找到了您需要修改的纪录的信息如下\n");
               printf("\n=================================\n");
               printf("\n会员号：%d\n",temp_str.ID);
               printf("\n会员名：%s\n",temp_str.sName);
               printf("\n密码：%s\n",temp_str.sPasswd);
               printf("\n等级：%d\n",temp_str.Level);
               printf("\n联系电话：%s\n",temp_str.sTelPhone);
               printf("\n=================================\n");
               printf("==========请修改会员信息:=========\n");
               printf("================================\n");
               printf("\t请输入会员ID:");
               scanf("%d",&temp_str.ID);
               printf("\t请输入用户名:");
               scanf("%s",temp_str.sName);
               printf("\t请设置密码:");
               scanf("%s",temp_str.sPasswd);
               printf("\t请输入会员级别:");
               scanf("%d",&temp_str.Level);
               printf("\t请输入用户电话:");
               scanf("%s",temp_str.sTelPhone);
               printf("================================\n");
               
          }
          else
          {
               printf("\n无此会员的信息，按任意键返回……\n");
               getchar();
               break;
          }
          printf("\n确定要修改吗？1：表示确定修改 0：表示取消修改");
          scanf("%d",&confirm);
          char ti=getchar();
          if(confirm==1)
          { 
           fseek(fp2,-sizeof(struct _USERINFO),1);//从当前位置处往前一个结构体的长度
           fwrite(&temp_str,sizeof(struct _USERINFO),1,fp2);//重写这一条记录
           printf("此会员的信息已经修改成功！！！");    
          }
         fclose(fp2);
         printf("\n要继续吗？（y/n）：");
         scanf("%c",&reply);
     } 
      printf("\n按任意键返回主菜单……\n");
      getchar();
     
    return ;
}





























































