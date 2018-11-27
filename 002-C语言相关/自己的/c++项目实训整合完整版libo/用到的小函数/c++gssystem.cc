#include<fstream> 
#include<iostream> 
#include<stdlib.h> 
#include<ctime> 
#include<cmath> 
#include<termios.h> 
#include <sstream> 
#include<string.h> 
#include<assert.h> 
#include<mysql/mysql.h> 
//改变字体颜色 

#define NONE "\033[m" 
#define RED "\033[0;32;31m" 
#define GREEN "\033[0;32;32m" 
#define BLUE "\033[0;32;34m" 
#define YELLOW "\033[1;33m" 
 
#define LIGHT_RED "\033[1;31m" 
#define LIGHT_GREEN "\033[1;32m" 
#define LIGHT_BLUE "\033[1;34m" 
/* 

在编译程序之前，请先开启
mysql
服务器（命令为sudo mysqld_safe &），然后再登录mysql客户端（命令为mysql -u root -p）建立数据库stu；建立数据表reader，book；具体操作语句如下：
create database stu; 
create table reader(stu_name 
varchar(20),stu_phone 
varchar(15),stu_password 
varchar(10),stu_num int,debt float,lend_time double,back_time double,count int); 
 

 
create table book(book_name 
varchar(40),book_aut 
varchar(40),book_pre 
varchar(40),book_num int,book_mux int,book_con int); 
 
编译时用如下命令：
g++ $(mysql_config --cflags) 110.cpp -o t $(mysql_config --libs) 
*/ 
 
//定义mysql数据库变量
MYSQL mysql; 
MYSQL_RES * results;  

MYSQL_FIELD *fileds;      
MYSQL_ROW rows;       
 char strHost[] = "localhost";     
 char strUser[] = "root";      
 char strPasswd[] = "3335599";      
 char strDb[] = "stu";  
 char strSQL[200];   
 unsigned int num_fields;  /* 
程序导读：  1.程序中对书的操作，可通过书名，编号来进行,flag=0按书名来操作,flag=1按书编号来操作  2.程序中对用户的操作，也可通过姓名，用户ID号或编号两种方式来进行,flag=0按姓名来操作,    flag=1按用户ID号或编号来操作  3.本程序分5个部分，具体已标识如（1）图书管理...  4.本程序即可实现将数据保存至本地即stu.txt,book.txt，又可将数据保存至mysql数据库，只    需稍加修改，具体如何修改，在此就不做说明 */  
using namespace std; class Book {  public:  string book_name;  string book_num;//编号  string book_pre;//出版社  string book_aut;//作者  int book_con;//这样的书还有几本  int book_mux;//这样的书总共有几本  public:  Book(){book_con=0;book_mux=0;}  void show_book();   };  
/****************************************（1）图书管理*******************************************/ 
void Book::show_book() 
{ 
	3 
 
 cout<<"书名："<<book_name<<endl;  
 cout<<"出版社："<<book_pre<<endl;
   cout<<"此书的作者："<<book_aut<<endl;  
   cout<<"ISBN编号："<<book_num<<endl;  
   cout<<"此书共有"<<book_mux<<"本"<<endl;  
   cout<<"还有"<<book_con<<"本书未借出！"<<endl; 
   
}   
class BookNode {  public:  Book book;  BookNode *next; }; 
BookNode *headbook=NULL;  
void savebook(BookNode *p);//保存图书信息到数据库 
void del_sql_book(BookNode *p);//将图书信息从数据库中删除  
class BookManage 
{   public:  int totolbook; 
 public:  BookManage(){totolbook=0;}  
 void addbook();   
 void delbook(string s,int num,int flag);  
 void findbook(string s,int flag);//查询图书 };  
void BookManage::addbook() 
{  string h;  
cout<<"添加输入0，退出输入-1"<<endl;  
cin>>h; 
 if(h=="-1")return;  
 else if(h=="0")  
 while(1)  
 {     
 if(h=="-1")
 break;  
  else if(h=="0")  
 { 
 string na,nu,p1,aut;
 int con;    
 BookNode *p=new BookNode;    
 cout<<"请输入书名："<<endl;    
 cin>>na; 
   p->book.book_name=na; 
   cout<<"请输入ISBN编号："<<endl;    
   cin>>nu; 
   p->book.book_num=nu; 
   cout<<"请输入出版社："<<endl;    
   cin>>p1; 
   p->book.book_pre=p1; 
   cout<<"请输入此书的作者："<<endl;    
   cin>>aut; 
   p->book.book_aut=aut; 
   cout<<"请输入此书共有几本："<<endl;    
   cin>>con; 
   p->book.book_con=con;    
   p->book.book_mux=con;    
   p->next=headbook;    
   headbook=p; 
   savebook(p);//添加至数据库  
  
BookManage::totolbook+=con; 
   cout<<"继续添加输入0，取消添加输入-1"<<endl;    
   cin>>h;   }   
   else   cout<<YELLOW"输入字符无效！"NONE<<endl;  
   }  
   else  cout<<YELLOW"输入字符无效！"NONE<<endl; 
   }  

void BookManage::delbook(string s,int num,int flag) 
{  
BookNode *p=headbook;  
if(headbook!=NULL)  
{   switch(flag)  
 {    case 0:      
 if(headbook->book.book_name==s)    
  {     
   if(headbook->book.book_con>1)      
   {headbook->book.book_con-=num;
   headbook->book.book_mux-=num;} 
   
   else      {       
   headbook=p->next;      
    totolbook-=num; 
      
      del_sql_book(p);//从数据库中删除 
      //delete p;      }     }      else if(p->next)     {        for(p=headbook;p->next!=NULL&&p!=NULL;p=p->next)      {            if(p->next->book.book_name==s)       {        if(p->next->book.book_con>1)        {         
 p->next->book.book_con-=num;headbook->book.book_mux-=num;         
 break;        
 }        
 else        
 {         
 p->next=p->next->next;         
 totolbook-=num;         
 del_sql_book(p->next);//从数据库中删除         //delete p->next;         break;        }       }          }      if(p->next==NULL)      cout<<YELLOW"此书不存在！"NONE<<endl;     }        break;    case 1:      if(headbook->book.book_num==s)     {      if(headbook->book.book_con>1)      {headbook->book.book_con-=num;headbook->book.book_mux-=num;}      else      {       headbook=p->next;       totolbook-=num;  
   del_sql_book(p);//从数据库中删除 

//delete p;      }     }      else if(p->next)     {        for(p=headbook;p->next!=NULL&&p!=NULL;p=p->next)      {            if(p->next->book.book_num==s)       {        if(p->next->book.book_con>1)        {        
 p->next->book.book_con-=num;
 headbook->book.book_mux-=num;         
 break;       
  }        
  else        
  {         
  p->next=p->next->next;         
  totolbook-=num;         
  del_sql_book(p->next);//从数据库中删除         //delete p->next;         break;        }       }          }      if(p->next==NULL)      cout<<YELLOW"此书不存在！"NONE<<endl;     }        break;    default: 
    
    cout<<YELLOW"输入数字无效！"NONE<<endl;break;   
    }  
    } 
    }   
void BookManage::findbook(string s,int flag) 
{  BookNode *p; 
int h=0;  
switch(flag)  
{   
case 0:      
for(p=headbook;p!=NULL;p=p->next)//先查看是否有此书    
{ 

if(p->book.book_name==s)    
 break;   
 } 
   
   if(NULL==p) 
   cout<<YELLOW"此书不存在！"NONE<<endl; 
    for(p=headbook;p!=NULL;p=p->next)//查看名为s的图书共有几本    
    {     
    if(p->book.book_name==s)     
    h++;   
     } 
   if(h>0) 
  
 
 
cout<<GREEN"这种名字的书共有"<<h<<"本"NONE<<endl; 
 
   
for(p=headbook;p!=NULL;p=p->next)//查看图书，把所有名为s的图书的信息都打印出来    
{            
 if(p->book.book_name==s)    
  {      
  p->book.show_book();//显示出图书的基本信息                 
 if(p->book.book_con==0) 
     cout<<YELLOW"该书已全被借出！"
     NONE<<endl;      
     cout<<endl;    
      }   
       }    
       break;  
        case 1:    
        for(p=headbook;p!=NULL;p=p->next)    
        {     
        if(p->book.book_num==s)    
         {      
         p->book.show_book();           
          if(p->book.book_con==0)      
          cout<<YELLOW"该书已全被借出！"
          NONE<<endl;break;     
          }    
          }    
          if(NULL==p)    
          cout<<YELLOW"此书不存在！"NONE<<endl;    
          break;   
          default:    
          cout<<YELLOW"输入数字无效！"
          NONE<<endl;
          break; 
} 

}


