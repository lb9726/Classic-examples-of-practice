#include "ui.h"
 
    
int main(int argc,char **argv)
{   
  
   pid_t pid;
   pid=fork();
   
   int h,m,s,h1,m1,s1;  
   int i=3;
   int sum=-1;
   char str[20];
   char logintime[30];
   struct tm *p;
   time_t t;
   DataBase db;
   string str1;
  
   FILE *fp;
   fp=fopen("2.txt","w");  //清空重定向文件的内容
   fclose(fp);
   fp=NULL;
   

 
   
  
   db.initDB("localhost" , "root", "123" , "Company" );
   str1="select *from time";
   db.executeSQL(str1);
   db.res = mysql_store_result(db.connection);
   //获取上次因输入错误超过三次时 的时间
   while((db.row=mysql_fetch_row(db.res))!=NULL)    
   {
        h = atoi(db.row[0]);   
        m=atoi(db.row[1]);
        s=atoi(db.row[2]);
   } 
   
   
   do             //一分钟之内不能登陆
   {
        t=time(NULL);              //获取随机数种子
        p=localtime(&t);
        h1=p->tm_hour;             //获取当前系统时间
        m1=p->tm_min;
        s1=p->tm_sec;
        if(h1<h)
        {
	     h1=h1+24-h;
        }
        else
             h1=h1-h;
        if(m1<m)
        {
	     m1=m1+60-m;
             h1--;
        }
        else
             m1=m1-m;
        if(s1<s)
        {
	     s1=s1+60-s;
             m1--;
        }
        else
            s1=s1-s;

        sum=h1*3600+m1*60+s1;
        if(sum>60)
            break;
        sleep(1);
        system("clear");
        cout<<"\n\n\n\n\n"; 
 
        printf("\t\t\033[33;32m 您还有%ds才可以登陆！ \033[0m\n\n",60-sum);
        //system("cowsay -f tux 坑爹啊");
        cout<<endl;
    }while(sum<60);
    
   if(pid>0)
   { 
     
    do
    {
      
       switch(Login())   //按条件进入
       {
          case 1:
             sleep(1);
             BossUI();  //boss界面
             break;
          case 2:
             sleep(1);
            
             ManagerUI();  //经理       
             break;
          case 3:
             sleep(1);
             Sell_ManagerUI();  //销售经理
             break;
          case 4:
             sleep(1);
             EmployeeUI();  //兼职技术人员
             break;
          case 5:
             sleep(1);
             EmployeeUI();  //兼职销售人员
             break;   
          case 6:
            cout<<"\t\t\033[33;32m 输入错误！请重新输入！ \033[0m\n\n";
            sleep(1);     
            break;
       }
    
       i--;     //登陆次数自加
    
    }while(i>0);

   t=time(NULL);
   p=localtime(&t);
   str1="delete from time";                //清空表中的内容
   db.executeSQL(str1);
   sprintf(str,"insert into time values(%d,%d,%d)",p->tm_hour,p->tm_min,p->tm_sec);
   db.executeSQL(str);
   cout<<"\t\t\033[33;32m 输入错误三次！请一分钟之后登陆！ \033[0m\n\n"<<endl;
   sleep(1);
   system("sl");
   
   //关闭音乐播放 kill ID
   char S[48];
   char buff[48];
  // FILE *fp;
   fp=fopen("2.txt","r");
   fgets(buff,6,fp);
   //fp=fopen("2.txt","w");  //清空重定向文件的内容
   fclose(fp);
   fp=NULL;
   int l;
   l=(buff[1]-48)*1000 +(buff[2]-48)*100 + (buff[3]-48)*10 + (buff[4]-48); 
   sprintf(S,"kill %d",l);
   system(S);
   
   exit(0);
   
   }//if 父进程
        
   if(pid==0)   //pid = 0表示是子进程，pid > 0表示是父进程
     {
      
      init_daemon();
      system("mplayer  /home/hyw/桌面/music/邓紫棋-你把我灌醉.wav cat foo >home/hyw/桌面/C++公司管理系统/1.txt 2>&1  &"); // '&' 放到后台
      system("ps -e|grep mplayer >>/home/hyw/桌面/C++公司管理系统/hyw4/2.txt ");  //获取 进程ID 
    
     }//if子进程
     
   
   
}







