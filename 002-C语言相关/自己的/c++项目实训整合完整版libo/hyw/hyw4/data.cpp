#include "data.h"

/*初始化数据库放在构造函数中*/
DataBase::DataBase()
{
   connection = mysql_init(NULL);
   if(connection == NULL)
   {
	perror("mysql_init");
        exit(1);
   }
}

/*析构函数*/
DataBase::~DataBase()
{
    if(connection!=NULL)
    {   //关闭数据库
	mysql_close(connection);
    }
}


//调用数据库SQL语句
bool DataBase::executeSQL(string sql_str)
{
    mysql_set_character_set(connection,"utf8");
    if(mysql_query(connection,sql_str.c_str()))
    {
	printf("Error making query:%s\n",mysql_error(connection));
        exit(1);
    }
    return true;
}

bool DataBase::initDB(string server_host,string user,string passwd,string db_name)
{
    //初始化数据库句柄
    connection = mysql_init(NULL);
    connection = mysql_real_connect(connection,server_host.c_str(),user.c_str(),passwd.c_str(),db_name.c_str(),0,NULL,0);
    if(connection==NULL)
    {
   	cout<<"connect error"<<endl;
        return 0;
    }  
    return true;
}


//======================================================
void  Emaction::Showown(int id)
{
     string str;
     db.initDB("localhost" , "root", "123" , "Company" );
     list<Employee>m;
     Employee em;
     str="select *from user";
     db.executeSQL(str);
     db.res = mysql_store_result(db.connection);
     
     system("clear");
     cout<<'\n';
     cout<<"\t\t\033[34;32m       ************************************      \n";
     cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
     cout<<"\n\n\n";
    
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
          if(atoi(db.row[0])==id)
          {
               cout<<"\t\t\033[42;31m+-----------+---------+------+-----+--------------------+------+-----------+-----------+------------+\033[0m"<<endl;
               cout<<"\t\t\033[42;31m|编号       |姓名     |年龄  | 性别|    职位            | 等级 |    工资   | 密码      |电话        |\033[0m"<<endl;
               cout<<"\t\t\033[42;31m+-----------+---------+------+-----+--------------------+------+-----------+-----------+------------+\033[0m"<<endl;
                if(strcmp(db.row[4],"兼职技术人员")==0)
                    printf("\t\t\033[42;31m|%-10s | %-8s  | %-5s| %-5s| %-18s       |  %-5s| %-10s| %-10s|%-12s|\033[0m\n",
                      db.row[0],db.row[1],db.row[2],db.row[3],db.row[4],db.row[5],db.row[6],db.row[7],db.row[8]);
                if(strcmp(db.row[4],"兼职销售人员")==0)
                    printf("\t\t\033[42;31m|%-10s | %-8s  | %-5s| %-5s| %-18s       | %-5s| %-10s| %-10s|%-12s|\033[0m\n",
                      db.row[0],db.row[1],db.row[2],db.row[3],db.row[4],db.row[5],db.row[6],db.row[7],db.row[8]);
             //每列的信息    
                else if(strcmp(db.row[4],"销售经理")==0)
                    printf("\t\t\033[42;31m|%-10s | %-8s  | %-5s| %-5s| %-18s     |  %-5s| %-10s| %-10s|%-12s|\033[0m\n",
                      db.row[0],db.row[1],db.row[2],db.row[3],db.row[4],db.row[5],db.row[6],db.row[7],db.row[8]);
                else if(strcmp(db.row[4],"经理")==0)
                    printf("\t\t\033[42;31m|%-10s | %-8s  | %-5s| %-5s| %-18s   | %-5s| %-10s| %-10s|%-12s|\033[0m\n",
                     db.row[0],db.row[1],db.row[2],db.row[3],db.row[4],db.row[5],db.row[6],db.row[7],db.row[8]);
               break;
          }
     } 
     cout<<"\t\t\033[42;31m+-----------+---------+------+-----+--------------------+------+-----------+-----------+------------+\033[0m"<<endl;
     End();
}
void  Emaction::Chpasswd(int id)
{
     string str;
     char s[100];
     char passwd1[48],passwd2[48],passwd3[48];
     db.initDB("localhost" , "root", "123" , "Company" );
     list<Employee>m;
     Employee em;
     str="select *from user";
     db.executeSQL(str);
     db.res = mysql_store_result(db.connection);
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);
        
        m.push_back(em);
     } 
     list<Employee>::iterator it=m.begin();
     
     system("clear");
     cout<<'\n';
     cout<<"\t\t\033[34;32m       ************************************      \n";
     cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
     cout<<"\n\n\n"; 
     while(it!=m.end())
     {   
	 if(it->m_Number==id)
         {
              cout<<"\t\t\033[34;32m 请输入原先的密码： \033[0m";
              cin>>passwd1;
              if(strcmp(it->m_passwd,passwd1)==0)
              {
                  while(1)
                  {   
                      cout<<'\n';
                      cout<<"\t\t\033[34;32m 请输入新的密码： \033[0m";
                      cin>>passwd2;
                      
                      cout<<'\n';
                      cout<<"\t\t\033[34;32m 请再次输入新的密码： \033[0m";
                      cin>>passwd3;
                      cout<<'\n';
                      
                      if(strcmp(passwd2,passwd3)==0)
                      {
	                   strcpy(it->m_passwd,passwd2);
                           break;
                      }
                      else
                          cout<<"\t\t\033[34;32m 密码不一致! \033[0m";
                          
                  }
              }
              break;
         }
         it++;
     }
      str="delete from user";                //清空表中的内容
      db.executeSQL(str);
      it=m.begin();  //it 迭代器
      while(it!=m.end())
      {
	  sprintf(s,"insert into user values(%d,'%s',%d,'%s','%s',%d,%d,'%s','%s')",
                       it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,
                       it->m_level,it->m_salary,it->m_passwd,it->m_Tel);
          db.executeSQL(s);
          it++;
          if(it==m.end())
              break;
      }
     cout<<"\t\t\033[34;32m 修改成功！ \033[0m\n";
     End();
}

//=========================================================
//添加员工信息
void Manager::Add()
{
    int i,sex;
    char str[100];

    list<Employee> m;  //容器
    Employee em;
    
    string s;
    s="select *from user"; 
    db.initDB("localhost" , "root", "123" , "Company" );
    db.executeSQL(s);   //查询数据库
    db.res = mysql_store_result(db.connection);     //接受结果集
    while((db.row=mysql_fetch_row(db.res))!=NULL)   //
    {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);
        
        m.push_back(em);
    } 
    while(1)
    {
        em.m_Number=Max(m)+1;

         system("clear");
         cout<<'\n';
         cout<<"\t\t\033[34;32m       ************************************      \n";
         cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
         cout<<"\n\n\n";  
       
        cout<<"\t\t\033[34;32m 姓名: \033[0m";
        cin>>em.m_Name;
        cout<<'\n';
        
        cout<<"\t\t\033[34;32m 年龄： \033[0m";
        cin>>em.m_age;
        cout<<'\n';
        
        cout<<"\t\t\033[34;32m 性别:（1.男 0.女） \033[0m";
        cin>>sex;
        cout<<'\n';
        
        if(sex==1)
           strcpy(em.m_sex,"男");
        else if(sex==0)
           strcpy(em.m_sex,"女");
        em.m_level=2;
        strcpy(em.m_position,"兼职技术人员");
        
        cout<<"\t\t\033[34;32m 工资： \033[0m";
        cin>>em.m_salary;  
        cout<<'\n';
        
        cout<<"\t\t\033[34;32m 电话： \033[0m";
        cin>>em.m_Tel;
        cout<<'\n';
        strcpy(em.m_passwd,"123");
        m.push_back(em);         //将数据信息 写到容器（list）中  m.
        
        cout<<"\t\t\033[34;32m 是否继续添加!(1是，0否)： \033[0m";
        cin>>i;
        cout<<'\n';
        if(i==0)
           break;
        else if(i==1)
           continue;
    }
      s="delete from user";                //清空表中的内容
      db.executeSQL(s);
      list<Employee>::iterator it=m.begin();  //it 迭代器
      while(it!=m.end())
      {
	  sprintf(str,"insert into user values(%d,'%s',%d,'%s','%s',%d,%d,'%s','%s')",
                       it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,
                       it->m_level,it->m_salary,it->m_passwd,it->m_Tel);
          db.executeSQL(str);
          it++;
          if(it==m.end())
              break;
      }
     End();
     //db.execute_select_SQL("select * from user");
}
/*
char *Gaintime(char *q)
{
    string str1;
    char str[100];
    struct tm *p;
    DataBase db;
   time_t t;
     str1="select *from logintime";
     db.executeSQL(str1);
    db.res = mysql_store_result(db.connection);
    while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
         sprintf(q,"%d-%d-%d %d:%d:%d",atoi(db.row[0]),atoi(db.row[1]),atoi(db.row[2]),atoi(db.row[3]),atoi(db.row[4]),atoi(db.row[5]));
     } 
   str1="delete from user";                //清空表中的内容
      db.executeSQL(str1);
   sprintf(str,"insert into time values(%d,%d,%d)",p->tm_hour,p->tm_min,p->tm_sec);
      db.executeSQL(str);

    t=time(NULL);
    p=localtime(&t);
    db.initDB("localhost" , "root", "123" , "Company" );
    sprintf(str,"insert into logintime values(%d,%d,%d,%d,%d,%d)",p->tm_year+1900,p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
    db.executeSQL(str1);
    return q;
}*/
/*删除员工*/
void Manager::Delete()
{
     int number;
     string str;
     char s[100];
     list<Employee>m;
     db.initDB("localhost" , "root", "123" , "Company" );
     Employee em;
     str="select *from user";
     db.executeSQL(str);
     db.res = mysql_store_result(db.connection);
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
         em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);
        
        m.push_back(em);
     } 
     
     system("clear");
     cout<<'\n';
     cout<<"\t\t\033[34;32m       ************************************      \n";
     cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
     cout<<"\n\n\n";
     cout<<"\t\t\033[34;32m 请输入： \033[0m\n";
     cin>>number;
     cout<<'\n';
     
     list<Employee>::iterator it=m.begin();
     int i=0;
     while(it!=m.end())
     { 
          if(it->m_Number==number)
          {   i++;
              if(strcmp(it->m_position,"兼职技术人员")==0)
              {
                 m.erase(it);
              }
              else 
                 cout<<"\t\t\033[34;32m 你没权利删除该员工！ \033[0m\n";
              break;
          }
          it++;
        
     }
     if(i==0)
     {
	cout<<"\t\t\033[34;32m 没该员工信息！ \033[0m\n";
     }
     else
     {
         char ch;
         cout<<"\t\t\033[34;32m 你确定要删除？(y/n)： \033[0m";
         cin>>ch;
         cout<<'\n';
        if(ch=='y')
        {
         str="delete from user";           //清空表中内容     
         db.executeSQL(str);
         it=m.begin();  //it 迭代器
         while(it!=m.end())
         {
	    sprintf(s,"insert into user values(%d,'%s',%d,'%s','%s',%d,%d,'%s','%s')",
                         it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,
                         it->m_level,it->m_salary,it->m_passwd,it->m_Tel);
            db.executeSQL(s);
            it++;
            if(it==m.end())
               break;
         } 
        }
     }
     cout<<"\t\t\033[34;32m 删除成功! \033[0m\n";
     End();
}


//==========================================================================
int Max(list<Employee>m)
{
    int Max=10000;                           //员工编号从10000开始
    int id=10000;
    list<Employee>::iterator it;
    
    list<Employee>::iterator ra;
    ra=m.begin();   //先容器按编号排好序
    for(it=m.begin();it!=m.end();it++)
    {
	for(ra=++it;ra!=m.end();ra++)
        {
	    if(it->m_Number>ra->m_Number)
            {
	        int temp;
                temp=it->m_Number;
                it->m_Number=ra->m_Number;
                ra->m_Number=temp;
            }
            
        }
        it--;
    }
    ra=m.begin();                             //编号重利用， 以及自动加1
    while(ra!=m.end())
    {   if(id<ra->m_Number-1)
        {
           Max=id;
           break;
        }
	if(ra->m_Number>Max)
            Max=ra->m_Number;
        ra++;
        id++;
    }
    return Max;
}

/*
         char code[10]={'\0'};                   
         char str[5];   //  定义传入的验证码
         Verification_code(str);    //生成验证码

*/

//传值    验证码
char Verification_code( char str[5])  //char str[5]; 获取五位的随机串
{
   
    srand((int)time(NULL));     //获得随机种子.(随时间生成不同的种子)
    int n;                      //用来随机判断随机串的某一位是数字还是字母
    int n1;                     //用来进一步判断究竟是生成大写字母还是小写字母.
    char c;                     //用来获取随机字符
    int num=0;
    
   // while(num<10000)//生成10000个验证码
   // {
        int i;
        for(i=0;i<5;i++)
         {
           n=(rand()%10+1);
           
           //人工设定字符串是字母或者数字的比例为7:3
           if(n<=3)
            {
              c=(rand()%10+'0');
              str[i]=c;
            }

           else
            {
              //进一步判断生成的随机字符是大写还是小写，比例为1:1
               n1=rand()%2+1;
               if(n1==1)
                {
                  c=(rand()%26+'a');
                  str[i]=c;
                }
 
                else
                {
                  c=(rand()%26+'A');
                  str[i]=c;
                }
            }
         }

    printf("\t\t\033[33;32m 验证码是: \033[0m");     //一组验证码

    for(i=0;i<5;i++)
    {
      printf("%c",str[i]);
    }
    
    printf("\n");
    num++;
    
 // }
 
}

//修改函数
void Manager::Change()
{
     
     char str[100];
     string s;
     char ch,passwd1[48],passwd2[48],passwd3[48];
     int choice,sex,number;
     db.initDB("localhost" , "root", "123" , "Company" );
     list<Employee>m;
     Employee em;
     s="select *from user";
     db.executeSQL(s);
     db.res = mysql_store_result(db.connection);
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);

        m.push_back(em);
     } 
     
     system("clear");
     cout<<'\n';
     cout<<"\t\t\033[34;32m       ************************************      \n";
     cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
     cout<<"\n\n\n";
     cout<<"\t\t\033[34;32m 请输入要修改的员工编号： \033[0m";
     cin>>number;
     cout<<'\n';
     list<Employee>::iterator it=m.begin();
     int i=0;
     while(it!=m.end())
     {
       if(number==it->m_Number)
       { i++;
         if(strcmp(it->m_position,"兼职技术人员")==0)
         {  
            cout<<"\t\t\033[34;32m 1.姓名                         2.年龄 \033[0m\n\n";
            cout<<"\t\t\033[34;32m 3.性别                         4.电话 \033[0m\n\n";
            cout<<"\t\t\033[34;32m 5.工资                                \033[0m\n\n";
            cout<<"\t\t\033[34;32m 请输入你要修改的员工信息选项： \033[0m";
            cin>>choice;
            cout<<'\n';
            switch(choice)
            {
	       case 1:
	              cout<<"\t\t\033[34;32m 请输入新的姓名: \033[0m";
                      cin>>it->m_Name;
                      cout<<'\n';
                      break;
               case 2:
                      cout<<"\t\t\033[34;32m 请输入新的年龄： \033[0m";
                      cin>>it->m_age;
                      cout<<'\n';
                      break;
               case 3:
                      cout<<"\t\t\033[34;32m 1,男 0，女： \033[0m";
                      cin>>sex;
                      cout<<'\n';
                      if(sex==1)
                         strcpy(it->m_sex,"男");
                      else if(sex==0)
                         strcpy(it->m_sex,"女");
                      break;
               case 4:
                      cout<<"\t\t\033[34;32m 请输入新的电话号码: \033[0m";
                      cin>>it->m_Tel;
                      cout<<'\n';
                      break;
               case 5:
                      cout<<"\t\t\033[34;32m 请输入新的工资: \033[0m";
                      cin>>it->m_salary;
                      cout<<'\n';
                      break;
              
               default:
                      break;
              }
           }
           else
               cout<<"\t\t\033[34;32m 该员工不在你的范围之内！ \033[0m\n";
               break;
         }
         
           it++;
       }
    if(i==0)
      cout<<"\t\t\033[34;32m 没该编号的员工！ \033[0m\n";
    else
    { 
      cout<<"\t\t\033[34;32m 确认要更改吗？（y/n）: \033[0m";
      cin>>ch;
      cout<<'\n';
      if(ch=='y')
      {   
          s="delete from user";           //清空表中内容     
          db.executeSQL(s);
          it=m.begin();
	    //it 迭代器
          while(it!=m.end())
          {   
	      sprintf(str,"insert into user values(%d,'%s',%d,'%s','%s',%d,%d,'%s','%s')",
                       it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,
                       it->m_level,it->m_salary,it->m_passwd,it->m_Tel);
              db.executeSQL(str);
              it++;
              if(it==m.end())
                 break;
          }
          cout<<"\t\t\033[34;32m 更改成功！ \033[0m\n";
          End();
          return;
      } 
      else  if(ch=='n')
         return;
     }
      End();
}


//结束处理
void End()
{
    cout<<"\n\n";
    cout<<"\t\t\033[34;32m please press anykey to continue.... \033[0m\n";
    while(getchar()!='\n');
    getchar();
    
}

//============================================================================
//查找
void Manager::Search()
{
     int number,choice;
     char name[48]; 
     string s;
     db.initDB("localhost" , "root", "123" , "Company" );
     list<Employee>m;
     Employee em;
     s="select *from user";
     db.executeSQL(s);
     db.res = mysql_store_result(db.connection);
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);

        m.push_back(em);
     } 
    
     system("clear");
     cout<<'\n';
     cout<<"\t\t\033[34;32m       ************************************      \n";
     cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
     cout<<"\n\n\n";
     
     cout<<"\t\t\033[34;32m 1.按人名查询                        2.按编号查询\033[0m\n\n";
     cout<<"\t\t\033[34;32m 请输入你的选择 ：\033[0m";
     cin>>choice;
     cout<<'\n';
     
     int i=0;
     if(choice==2)
     {
        cout<<"\t\t\033[34;32m 请输入要查询的编号: \033[0m";
        cin>>number;
        cout<<'\n';
        
       
        list<Employee>::iterator it=m.begin();
        
        while(it!=m.end())
        {
	   if(it->m_Number==number)
           {  i++;
              if(strcmp(it->m_position,"兼职技术人员")==0)
              {
               cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
                    cout<<"\t\t\033[46;31m|编号       |姓名     |年龄  | 性别|    职位            | 等级 |    工资   |电话         |\033[0m"<<endl;
                    cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
                    printf("\t\t\033[42;31m|%-10d | %-8s  | %-5d| %-5s| %-18s     | %-5d| %-10d| %-12s|\033[0m\n",
                      it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,it->m_level,it->m_salary,it->m_Tel);
               } 
              else 
                 cout<<"\t\t\033[34;32m 该员工不在你的管辖范围! \033[0m\n";
                break; 
           }
           it++;
        }
        if(i==0)
          cout<<"\t\t\033[34;32m 没该编号的员工! \033[0m\n";
     }
     else if(choice==1)
     {
        cout<<"\t\t\033[34;32m 请输入要查询的姓名: \033[0m";
        cin>>name;
        cout<<'\n';
        
        
        list<Employee>::iterator it=m.begin();
        while(it!=m.end())
        {  i++;
	   if(strcmp(it->m_Name,name)==0)
           {
               if(strcmp(it->m_position,"兼职技术人员")==0)
               {cout<<"\t\t\033[34;32m 编号    姓名    年龄    性别    职位   等级     电话    工资 \033[0m\n";
	          cout<<it->m_Number <<'\t' <<it->m_Name <<'\t' <<it->m_age <<'\t' <<
                    it->m_sex <<'\t' <<it->m_position<<'\t' <<it->m_level <<'\t' <<
                   it->m_salary <<'\t' <<it->m_Tel<<endl; //每列的信息
               }
               else
                 cout<<"\t\t\033[34;32m 该员工不在你的管辖范围！ \033[0m";
                break; 
           }
           it++;
        }
        if(i==0)
           cout<<"\t\t\033[34;32m 没该编号的员工! \033[0m\n";
     }
     End();
}
//显示信息
void Manager::Show()
{
    string s;
    s="select *from user"; 
    db.initDB("localhost" , "root", "123" , "Company" );
    db.executeSQL(s);   //查询数据库
    db.res = mysql_store_result(db.connection);     //接受结果集
    
    system("clear");
    cout<<'\n';
    cout<<"\t\t\033[34;32m       ************************************      \n";
    cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
    cout<<"\n\n\n"; 
    
    cout<<"\t\t\033[42;31m+-----------+-------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
    cout<<"\t\t\033[42;31m|编号       |姓名   |年龄  | 性别|    职位            | 等级 |    工资   |电话         |\033[0m"<<endl;
    cout<<"\t\t\033[42;31m+-----------+-------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
    
    while((db.row=mysql_fetch_row(db.res))!=NULL)   //
    {
         if(strcmp(db.row[4],"兼职技术人员")==0)
         {

             printf("\t\t\033[46;31m|%-10s | %-8s| %-5s| %-5s| %-25s| %-5s| %-10s| %-12s|\033[0m\n",db.row[0],db.row[1],db.row[2],db.row[3],db.row[4],db.row[5],db.row[6],db.row[8]);
             //每列的信息 
         }   
    } 
    cout<<"\t\t\033[42;31m+-----------+-------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
    End();
}


/*BOSS的增删改差*/
/******************************************************************************/
void Boss::Add()
{
    int i,sex;
    char str[100];

    list<Employee> m;  //容器
    Employee em;
    
    string s;
    s="select *from user"; 
    db.initDB("localhost" , "root", "123" , "Company" );
    db.executeSQL(s);   //查询数据库
    db.res = mysql_store_result(db.connection);     //接受结果集
    while((db.row=mysql_fetch_row(db.res))!=NULL)   //
    {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);
        
        m.push_back(em);
    } 
    while(1)
    {
        system("clear");
        cout<<'\n';
        cout<<"\t\t\033[34;32m       ************************************      \n";
        cout<<"\t\t\033[34;32m**************欢迎BOSS登陆公司管理系统*****************\033[0m\n\n\n"; 
        cout<<"\n\n\n"; 
        
        em.m_Number=Max(m)+1;
        cout<<"\t\t\033[34;32m 姓名: \033[0m"; 
        cin>>em.m_Name;
        cout<<'\n';
        
        cout<<"\t\t\033[34;32m 年龄： \033[0m"; 
        cin>>em.m_age;
        cout<<'\n';
        
        cout<<"\t\t\033[34;32m 性别:（1.男 0.女）: \033[0m"; 
        cin>>sex;
        cout<<'\n';
        
        if(sex==1)
           strcpy(em.m_sex,"男");
        else if(sex==0)
           strcpy(em.m_sex,"女");
        cout<<"\t\t\033[34;32m 1.经理             2.销售经理 \033[0m\n"; 
        cout<<"\t\t\033[34;32m 3.兼职技术人员     4.兼职销售人员 \033[0m\n\n"; 
        cout<<"\t\t\033[34;32m 请选择自己所属职称: \033[0m"; 
        cin>>em.m_level;
        cout<<'\n';
        
        switch(em.m_level)
        {
	    case 1:
               strcpy(em.m_position,"经理");
               break;
            case 2:
               strcpy(em.m_position,"销售经理");
               break;
            case 3:
               strcpy(em.m_position,"兼职技术人员");
               break;
            case 4:
               strcpy(em.m_position,"兼职销售人员");
               break;
        }
        if(em.m_level<=2)
            em.m_level=1;
        else
            em.m_level=2;
        cout<<"\t\t\033[34;32m 工资: \033[0m"; 
        cin>>em.m_salary; 
        cout<<'\n';
           
        cout<<"\t\t\033[34;32m 电话： \033[0m"; 
        cin>>em.m_Tel;
        cout<<'\n';
        
        strcpy(em.m_passwd,"123");
        m.push_back(em);         //将数据信息 写到容器（list）中  m.
        cout<<"\t\t\033[34;32m 是否继续添加!(1是，0否)： \033[0m"; 
        cin>>i;
        cout<<'\n';
        if(i==0)
           break;
        else if(i==1)
           continue;
     }
      s="delete from user";                //清空表中的内容
      db.executeSQL(s);
      list<Employee>::iterator it=m.begin();  //it 迭代器
      while(it!=m.end())
      {
	  sprintf(str,"insert into user values(%d,'%s',%d,'%s','%s',%d,%d,'%s','%s')",
                       it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,
                       it->m_level,it->m_salary,it->m_passwd,it->m_Tel);
          db.executeSQL(str);
          it++;
          if(it==m.end())
              break;
      }
      End();
}


void Boss::Delete()
{
     int number;
     string str;
     int i=0;
     char s[100];
     list<Employee>m;
     db.initDB("localhost" , "root", "123" , "Company" );
     Employee em;
     str="select *from user";
     db.executeSQL(str);
     db.res = mysql_store_result(db.connection);
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);
        
        m.push_back(em);
     } 
     
     system("clear");
     cout<<'\n';
     cout<<"\t\t\033[34;32m       ************************************      \n";
     cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
     cout<<"\n\n\n";
     cout<<"\t\t\033[34;32m 请输入要删除的员工编号: \033[0m"; 
     cin>>number;
     cout<<'\n';
     list<Employee>::iterator it=m.begin();
 
     //list<Employee>::iterator ra=m.begin();  //it 迭代器
     while(it!=m.end())
     { 
          if(it->m_Number==number)
          {  i++;
             m.erase(it);
             break;
          }
          it++;
        
     }
     if(i==0)
     {
	 cout<<"\t\t\033[34;32m 没该编号的员工! \033[0m\n"; 
     }
     else
     { char ch;
       cout<<"\t\t\033[34;32m 你确定要删除？(y/n)： \033[0m"; 
       cin>>ch;
       cout<<'\n';
       if(ch=='y')
       {
       str="delete from user";           //清空表中内容     
       db.executeSQL(str);
       it=m.begin();  //it 迭代器
       while(it!=m.end())
       {
	  sprintf(s,"insert into user values(%d,'%s',%d,'%s','%s',%d,%d,'%s','%s')",
                         it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,
                         it->m_level,it->m_salary,it->m_passwd,it->m_Tel);
          db.executeSQL(s);
          it++;
          if(it==m.end())
               break;
       }
          cout<<"\t\t\033[34;32m 删除成功！ \033[0m\n"; 
       } 
     }
     End();
}

void Boss::Show()
{
    string s;
    s="select *from user"; 
    db.initDB("localhost" , "root", "123" , "Company" );
    db.executeSQL(s);   //查询数据库
    db.res = mysql_store_result(db.connection);     //接受结果集
    
    system("clear");
    cout<<"\t\t\033[34;32m     *************************************      \n";
    cout<<"\t\t\033[34;32m***********欢迎BOSS登陆公司管理系统************\033[0m\n\n\n";
    cout<<"\n\n\n";  
    cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
    cout<<"\t\t\033[46;31m|编号       |姓名     |年龄  | 性别|    职位            | 等级 |    工资   |电话         |\033[0m"<<endl;
    cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
    while((db.row=mysql_fetch_row(db.res))!=NULL)   //
    {
        if(strcmp(db.row[4],"兼职技术人员")==0)
             printf("\t\t\033[42;31m|%-10s | %-8s  | %-5s| %-5s| %-18s       | %-5s| %-10s| %-12s|\033[0m\n",db.row[0],db.row[1],db.row[2],db.row[3],db.row[4],db.row[5],db.row[6],db.row[8]);
        if(strcmp(db.row[4],"兼职销售人员")==0)
             printf("\t\t\033[42;31m|%-10s | %-8s  | %-5s| %-5s| %-18s       | %-5s| %-10s| %-12s|\033[0m\n",db.row[0],db.row[1],db.row[2],db.row[3],db.row[4],db.row[5],db.row[6],db.row[8]);
             //每列的信息    
         else if(strcmp(db.row[4],"销售经理")==0)
              printf("\t\t\033[42;31m|%-10s | %-8s  | %-5s| %-5s| %-18s     | %-5s| %-10s| %-12s|\033[0m\n",db.row[0],db.row[1],db.row[2],db.row[3],db.row[4],db.row[5],db.row[6],db.row[8]);
         else if(strcmp(db.row[4],"经理")==0)
              printf("\t\t\033[42;31m|%-10s | %-8s  | %-5s| %-5s| %-18s   | %-5s| %-10s| %-12s|\033[0m\n",db.row[0],db.row[1],db.row[2],db.row[3],db.row[4],db.row[5],db.row[6],db.row[8]);
    } 
    cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
    End();
}

void Boss::Change()
{
     char str[100];
     string s;
     int i=0;
     char ch,passwd1[48],passwd2[48],passwd3[48];
     int choice,sex,number;
     db.initDB("localhost" , "root", "123" , "Company" );
     list<Employee>m;
     Employee em;
     s="select *from user";
     db.executeSQL(s);
     db.res = mysql_store_result(db.connection);
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);

        m.push_back(em);
     } 
     
     system("clear");
     cout<<"\t\t\033[34;32m     *************************************      \n";
     cout<<"\t\t\033[34;32m***********欢迎BOSS登陆公司管理系统************\033[0m\n\n\n";
     cout<<"\n\n\n";  
     cout<<"\t\t\033[34;32m 请输入要修改的员工编号： \033[0m";
     cin>>number;
     cout<<'\n';
     
     list<Employee>::iterator it=m.begin();
     while(it!=m.end())
     {
       if(number==it->m_Number)
       {  i++;
          cout<<"\t\t\033[34;32m 1.姓名             2.年龄 \033[0m\n";
          cout<<"\t\t\033[34;32m 3.性别             4.职位 \033[0m\n";
          cout<<"\t\t\033[34;32m 5.电话             6.工资 \033[0m\n\n";
          cout<<"\t\t\033[34;32m 请输入要修改的员工信息： \033[0m";
          cin>>choice;
          cout<<'\n';
        
          switch(choice)
          {
	     case 1:
                    cout<<"\t\t\033[34;32m 请输入新的姓名: \033[0m";
                    cin>>it->m_Name;
                    cout<<endl;
                    break;
             case 2:
                   cout<<"\t\t\033[34;32m 请输入新的年龄: \033[0m";
                   cin>>it->m_age;
                   cout<<endl;
               break;
             case 3:
                 cout<<"\t\t\033[34;32m 1,男 0，女 \033[0m";
                 cin>>sex;
                 cout<<'\n';
                 if(sex==1)
                    strcpy(it->m_sex,"男");
                 else if(sex==0)
                    strcpy(it->m_sex,"女");
                 break;
            case 4:
                 cout<<"\t\t\033[34;32m 1.经理             2.销售经理 \033[0m\n";
                 cout<<"\t\t\033[34;32m 3.兼职技术人员      4.兼职销售人员 \033[0m\n";
                 cout<<"\t\t\033[34;32m 请选择自己所属职称： \033[0m";
                 cin>>it->m_level;
                 cout<<'\n';
                 switch(it->m_level)
                 {
	            case 1:
                        strcpy(it->m_position,"经理");
                        break;
                    case 2:
                        strcpy(it->m_position,"销售经理");
                        break;
                    case 3:
                        strcpy(it->m_position,"兼职技术人员");
                        break;
                    case 4:
                        strcpy(it->m_position,"兼职销售人员");
                        break;
                    default:
                        break;
                 }
                break;
             case 5:
                    cout<<"\t\t\033[34;32m 请输入新的电话号码: \033[0m";
                    cin>>it->m_Tel;
                    cout<<endl;
                    break;
             case 6:
                    cout<<"\t\t\033[34;32m 请输入新的工资: \033[0m";
                    cin>>it->m_salary;
                    cout<<endl;
                    break;
             default:
                break;
            }
         }
         it++;
      }
      if(i==0)
          cout<<"\t\t\033[34;32m 没该编号的员工！ \033[0m\n";
      else
      {
         cout<<"\t\t\033[34;32m 确认要更改吗？（y/n）: \033[0m";
         cin>>ch;
         cout<<'\n';
         if(ch=='y')
         {   
          s="delete from user";           //清空表中内容     
          db.executeSQL(s);
          it=m.begin();
	    //it 迭代器
          while(it!=m.end())
          {   
	      sprintf(str,"insert into user values(%d,'%s',%d,'%s','%s',%d,%d,'%s','%s')",
                       it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,
                       it->m_level,it->m_salary,it->m_passwd,it->m_Tel);
              db.executeSQL(str);
              it++;
              if(it==m.end())
                 break;
          }
          cout<<"\t\t\033[34;32m 更改成功！ \033[0m\n";
          End();
          return;
      } 
      else  if(ch=='n')
         return;  
     } 
    End();
}

/*查询员工信息*/
void Boss::Search()
{
     int i=0;
     int number,choice;
     char name[48]; 
     string s;
     db.initDB("localhost" , "root", "123" , "Company" );
     list<Employee>m;
     Employee em;
     s="select *from user";
     db.executeSQL(s);
     db.res = mysql_store_result(db.connection);
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);

        m.push_back(em);
     } 
     
     system("clear");
     cout<<"\t\t\033[34;32m     *************************************      \n";
     cout<<"\t\t\033[34;32m***********欢迎BOSS登陆公司管理系统************\033[0m\n\n\n";
     cout<<"\n\n\n";  
     
     cout<<"\t\t\033[34;32m 1.按人名查询   2.按编号查询 \033[0m\n\n";
     cout<<"\t\t\033[34;32m 请选择： \033[0m";
     cin>>choice;
     cout<<'\n';
     if(choice==2)
     {
        cout<<"\t\t\033[34;32m 请输入要查询的编号: \033[0m";
        cin>>number;
        cout<<'\n';
        list<Employee>::iterator it=m.begin();
        while(it!=m.end())
        {
	   if(it->m_Number==number)
           {    i++;
                cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
    cout<<"\t\t\033[46;31m|编号       |姓名     |年龄  | 性别|    职位            | 等级 |    工资   |电话         |\033[0m"<<endl;
    cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
                if(strcmp(it->m_position,"兼职技术人员")==0)
                    printf("\t\t\033[42;31m|%-10d | %-8s  | %-5d| %-5s| %-18s     | %-5d| %-10d| %-12s|\033[0m\n",
                      it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,it->m_level,it->m_salary,it->m_Tel);
                if(strcmp(it->m_position,"兼职销售人员")==0)
                      printf("\t\t\033[42;31m|%-10d | %-8s  | %-5d| %-5s| %-18s     | %-5d| %-10d| %-12s|\033[0m\n",
                      it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,it->m_level,it->m_salary,it->m_Tel);
             //每列的信息    
                else if(strcmp(it->m_position,"销售经理")==0)
                      printf("\t\t\033[42;31m|%-10d | %-8s  | %-5d| %-5s| %-18s     | %-5d| %-10d| %-12s|\033[0m\n",
                      it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,it->m_level,it->m_salary,it->m_Tel);
                else if(strcmp(it->m_position,"经理")==0)
                       printf("\t\t\033[42;31m|%-10d | %-8s  | %-5d| %-5s| %-18s     | %-5d| %-10d| %-12s|\033[0m\n",
                      it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,it->m_level,it->m_salary,it->m_Tel);
                break; 
           }
           it++;
        }  
       if(i==0)
       {  
	  cout<<"\t\t\033[34;32m 没该编号的员工！ \033[0m\n";
       }
     }
    
     else if(choice==1)
     {
        cout<<"\t\t\033[34;32m 请输入要查询的姓名: \033[0m";
        cin>>name;
        cout<<'\n';
        list<Employee>::iterator it=m.begin();
        while(it!=m.end())
        {
	   if(strcmp(it->m_Name,name)==0)
           {
                i++;
                 cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
    cout<<"\t\t\033[46;31m|编号       |姓名     |年龄  | 性别|    职位            | 等级 |    工资   |电话         |\033[0m"<<endl;
    cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
                if(strcmp(it->m_position,"兼职技术人员")==0)
                    printf("\t\t\033[42;31m|%-10d | %-8s  | %-5d| %-5s| %-18s     | %-5d| %-10d| %-12s|\033[0m\n",
                      it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,it->m_level,it->m_salary,it->m_Tel);
                if(strcmp(it->m_position,"兼职销售人员")==0)
                      printf("\t\t\033[42;31m|%-10d | %-8s  | %-5d| %-5s| %-18s     | %-5d| %-10d| %-12s|\033[0m\n",
                      it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,it->m_level,it->m_salary,it->m_Tel);
             //每列的信息    
                else if(strcmp(it->m_position,"销售经理")==0)
                      printf("\t\t\033[42;31m|%-10d | %-8s  | %-5d| %-5s| %-18s     | %-5d| %-10d| %-12s|\033[0m\n",
                      it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,it->m_level,it->m_salary,it->m_Tel);
                else if(strcmp(it->m_position,"经理")==0)
                       printf("\t\t\033[42;31m|%-10d | %-8s  | %-5d| %-5s| %-18s     | %-5d| %-10d| %-12s|\033[0m\n",
                      it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,it->m_level,it->m_salary,it->m_Tel);
                break; 
           }
           it++;
        }
        if(i==0)
       {  
	  cout<<"\t\t\033[34;32m 没该姓名的员工！ \033[0m\n";
       }
     } 
    
     End();
}



//销售经理
//******************************************************************************

void Sell_manager::Add()
{
    int i,sex;
    char str[100];

    list<Employee> m;  //容器
    Employee em;
    
    string s;
    s="select *from user"; 
    db.initDB("localhost" , "root", "123" , "Company" );
    db.executeSQL(s);   //查询数据库
    db.res = mysql_store_result(db.connection);     //接受结果集
    while((db.row=mysql_fetch_row(db.res))!=NULL)   //
    {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);
        
        m.push_back(em);
    } 
    while(1)
    {
        system("clear");
        cout<<'\n';
        cout<<"\t\t\033[34;32m       ************************************      \n";
        cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
        cout<<"\n\n\n";
        
        em.m_Number=Max(m)+1;
        cout<<"\t\t\033[34;32m 姓名: \033[0m";
        cin>>em.m_Name;
        cout<<'\n';
        
        cout<<"\t\t\033[34;32m 年龄： \033[0m";
        cin>>em.m_age;
        cout<<'\n';
        
        cout<<"\t\t\033[34;32m 性别:（1.男 0.女） \033[0m";
        cin>>sex;
        cout<<'\n';
        if(sex==1)
           strcpy(em.m_sex,"男");
        else if(sex==0)
           strcpy(em.m_sex,"女");
        em.m_level=2;
        strcpy(em.m_position,"兼职销售人员");
        cout<<"\t\t\033[34;32m 工资 \033[0m";
        cin>>em.m_salary; 
        cout<<'\n';
          
        cout<<"\t\t\033[34;32m 电话： \033[0m";
        cin>>em.m_Tel;
        cout<<'\n';
        
        strcpy(em.m_passwd,"123");
        m.push_back(em);         //将数据信息 写到容器（list）中  m.
        cout<<"\t\t\033[34;32m 是否继续添加!(1是，0否) \033[0m";
        cin>>i;
        cout<<'\n';
        if(i==0)
           break;
        else if(i==1)
           continue;
    }
      s="delete from user";                //清空表中的内容
      db.executeSQL(s);
      list<Employee>::iterator it=m.begin();  //it 迭代器
      while(it!=m.end())
      {
	  sprintf(str,"insert into user values(%d,'%s',%d,'%s','%s',%d,%d,'%s','%s')",
                       it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,
                       it->m_level,it->m_salary,it->m_passwd,it->m_Tel);
          db.executeSQL(str);
          it++;
          if(it==m.end())
              break;
      }
}


//删除
void Sell_manager::Delete()
{
     int number;
     string str;
     char s[100];
     list<Employee>m;
     db.initDB("localhost" , "root", "123" , "Company" );
     Employee em;
     str="select *from user";
     db.executeSQL(str);
     db.res = mysql_store_result(db.connection);
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
         em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);
        
        m.push_back(em);
     } 
     
     system("clear");
     cout<<'\n';
     cout<<"\t\t\033[34;32m       ************************************      \n";
     cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
     cout<<"\n\n\n";
     cout<<"\t\t\033[34;32m 请输入： \033[0m\n";
     cin>>number;
     cout<<'\n';
     
     list<Employee>::iterator it=m.begin();
     int i=0;
     while(it!=m.end())
     { 
          if(it->m_Number==number)
          {   i++;
              if(strcmp(it->m_position,"兼职销售人员")==0)
              {
                 m.erase(it);
              }
              else 
                 cout<<"\t\t\033[34;32m 你没权利删除该员工！ \033[0m\n";
              break;
          }
          it++;
        
     }
     if(i==0)
     {
	cout<<"\t\t\033[34;32m 没该员工信息！ \033[0m\n";
     }
     else
     {
         char ch;
         cout<<"\t\t\033[34;32m 你确定要删除？(y/n)： \033[0m";
         cin>>ch;
         cout<<'\n';
        if(ch=='y')
        {
         str="delete from user";           //清空表中内容     
         db.executeSQL(str);
         it=m.begin();  //it 迭代器
         while(it!=m.end())
         {
	    sprintf(s,"insert into user values(%d,'%s',%d,'%s','%s',%d,%d,'%s','%s')",
                         it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,
                         it->m_level,it->m_salary,it->m_passwd,it->m_Tel);
            db.executeSQL(s);
            it++;
            if(it==m.end())
               break;
         } 
        }
     }
     cout<<"\t\t\033[34;32m 删除成功! \033[0m\n";
     End();
}


//修改
void Sell_manager::Change()
{
     
     char str[100];
     string s;
     char ch,passwd1[48],passwd2[48],passwd3[48];
     int choice,sex,number;
     db.initDB("localhost" , "root", "123" , "Company" );
     list<Employee>m;
     Employee em;
     s="select *from user";
     db.executeSQL(s);
     db.res = mysql_store_result(db.connection);
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);

        m.push_back(em);
     } 
     
     system("clear");
     cout<<'\n';
     cout<<"\t\t\033[34;32m       ************************************      \n";
     cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
     cout<<"\n\n\n";
     cout<<"\t\t\033[34;32m 请输入要修改的员工编号: \033[0m";
     cin>>number;
     cout<<'\n';
     
     list<Employee>::iterator it=m.begin();
     while(it!=m.end())
     {
       if(number==it->m_Number)
       {
         if(strcmp(it->m_position,"兼职销售人员")==0)
         {
            cout<<endl;
            cout<<"\t\t\033[34;32m 1.姓名                2.年龄 \033[0m\n";
            cout<<"\t\t\033[34;32m 3.性别                4.电话 \033[0m\n";
            cout<<"\t\t\033[34;32m 5.工资                       \033[0m\n";
            cout<<"\t\t\033[34;32m 请输入: \033[0m";
            cin>>choice; 
            cout<<'\n';
            
            switch(choice)
            {
	       case 1:
                      cout<<"\t\t\033[34;32m 请输入新的姓名: \033[0m";
                      cin>>it->m_Name;
                      cout<<endl;
                      break;
               case 2:
                      cout<<"\t\t\033[34;32m 请输入新的年龄: \033[0m";
                      cin>>it->m_age;
                      cout<<endl;
                      break;
               case 3:
                      cout<<"\t\t\033[34;32m 1,男 0，女 \033[0m";
                      cin>>sex;
                      cout<<endl;
                      if(sex==1)
                        strcpy(it->m_sex,"男");
                      else if(sex==0)
                        strcpy(it->m_sex,"女");
                      break;
               case 4:
                      cout<<"\t\t\033[34;32m 请输入新的电话号码: \033[0m";
                      cin>>it->m_Tel;
                      cout<<'\n';
                  break;
               case 5:
                      cout<<"\t\t\033[34;32m 请输入新的工资: \033[0m";
                      cin>>it->m_salary;
                      cout<<'\n';
                      break;
               default:
                      break;
              }
           }
           else
               cout<<"\t\t\033[34;32m 该员工不在你的管辖范围之内！ \033[0m\n";
           break;
         }
         
           it++;
       }
     
      cout<<"\t\t\033[34;32m 确认要更改吗？（y/n）: \033[0m";
      cin>>ch;
      cout<<'\n';
      if(ch=='y')
      {   
          s="delete from user";           //清空表中内容     
          db.executeSQL(s);
          it=m.begin();
	    //it 迭代器
          while(it!=m.end())
          {   
	      sprintf(str,"insert into user values(%d,'%s',%d,'%s','%s',%d,%d,'%s','%s')",
                       it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,
                       it->m_level,it->m_salary,it->m_passwd,it->m_Tel);
              db.executeSQL(str);
              it++;
              if(it==m.end())
                 break;
          }
          cout<<"\t\t\033[34;32m 更改成功! \033[0m\n";
          End();
          return;
      } 
      else  if(ch=='n')
          return;
      End();
}

//查找
void Sell_manager::Search()
{
     int number,choice;
     char name[48]; 
     string s;
     db.initDB("localhost" , "root", "123" , "Company" );
     list<Employee>m;
     Employee em;
     s="select *from user";
     db.executeSQL(s);
     db.res = mysql_store_result(db.connection);
     while((db.row=mysql_fetch_row(db.res))!=NULL)
     {
        em.m_Number = atoi(db.row[0]);   
        strcpy(em.m_Name , db.row[1]);
        em.m_age = atoi(db.row[2]);
        strcpy(em.m_sex , db.row[3]);
        strcpy(em.m_position , db.row[4]);
        em.m_level = atoi(db.row[5]); 
        em.m_salary=atoi(db.row[6]);
        strcpy(em.m_Tel, db.row[8]);
        strcpy(em.m_passwd,db.row[7]);

        m.push_back(em);
     }
     
     system("clear");
     cout<<'\n';
     cout<<"\t\t\033[34;32m       ************************************      \n";
     cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
     cout<<"\n\n\n";
     cout<<"\t\t\033[34;32m 1.按人名查询                   2.按编号查询 \033[0m\n\n";
     cout<<"\t\t\033[34;32m 请输入: \033[0m";
     cin>>choice;
     cout<<'\n';
     int i=0;
     if(choice==2)
     {
        cout<<endl;
        cout<<"\t\t\033[34;32m 请输入要查询的编号: \033[0m";
        cin>>number;
        cout<<'\n';
        
        list<Employee>::iterator it=m.begin();
        
        while(it!=m.end())
        {
	   if(it->m_Number==number)
           {  i++;
                if(strcmp(it->m_position,"兼职销售人员")==0)
                {
                    cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
                    cout<<"\t\t\033[46;31m|编号       |姓名     |年龄  | 性别|    职位            | 等级 |    工资   |电话         |\033[0m"<<endl;
                    cout<<"\t\t\033[46;31m+-----------+---------+------+-----+--------------------+------+-----------+-------------+\033[0m"<<endl;
                    printf("\t\t\033[42;31m|%-10d | %-8s  | %-5d| %-5s| %-18s     | %-5d| %-10d| %-12s|\033[0m\n",
                      it->m_Number,it->m_Name,it->m_age,it->m_sex,it->m_position,it->m_level,it->m_salary,it->m_Tel);
                }
              else 
                 cout<<"\t\t\033[34;32m 该员工不在你的管辖范围! \033[0m\n";
                break; 
           }
           it++;
        }
        if(i==0)
           cout<<"\t\t\033[34;32m 没该编号的员工! \033[0m\n";
     }
     else if(choice==1)
     {
        cout<<"\t\t\033[34;32m 请输入要查询的姓名: \033[0m";
        cin>>name;
        cout<<endl;
        cout<<"\t\t\033[34;32m 编号    姓名    年龄    性别    职位   等级     电话    工资 \033[0m\n";
        list<Employee>::iterator it=m.begin();
        while(it!=m.end())
        {  i++;
	   if(strcmp(it->m_Name,name)==0)
           {
               if(strcmp(it->m_position,"兼职销售人员")==0)
               {
	          cout<<it->m_Number <<'\t' <<it->m_Name <<'\t' <<it->m_age <<'\t' <<
                    it->m_sex <<'\t' <<it->m_position<<'\t' <<it->m_level <<'\t' <<
                   it->m_salary <<'\t' <<it->m_Tel<<endl; //每列的信息
               }
               else
                 cout<<"\t\t\033[34;32m 该员工不在你的管辖范围！ \033[0m\n";
                break; 
           }
           it++;
        }
        if(i==0)
          cout<<"\t\t\033[34;32m 没该编号的员工！ \033[0m\n";
     }
     End();
}
//显示信息
void Sell_manager::Show()
{
    string s;
    s="select *from user"; 
    db.initDB("localhost" , "root", "123" , "Company" );
    db.executeSQL(s);   //查询数据库
    db.res = mysql_store_result(db.connection);     //接受结果集
    
    system("clear");
    cout<<'\n';
    cout<<"\t\t\033[34;32m       ************************************      \n";
    cout<<"\t\t\033[34;32m**************欢迎登陆公司管理系统*****************\033[0m\n\n\n"; 
    cout<<"\n\n\n";
    cout<<"+-----------+-------+------+-----+--------------------+------+-----------+-------------+"<<endl;
    cout<<"|编号       |姓名   |年龄  | 性别|    职位            | 等级 |    工资   |电话         |"<<endl;
    cout<<"+-----------+-------+------+-----+--------------------+------+-----------+-------------+"<<endl;
    
    while((db.row=mysql_fetch_row(db.res))!=NULL)   //
    {
         if(strcmp(db.row[4],"兼职销售人员")==0)
         {

             printf("|%-10s | %-8s| %-5s| %-5s| %-25s| %-5s| %-10s| %-12s|\n",db.row[0],db.row[1],db.row[2],db.row[3],db.row[4],db.row[5],db.row[6],db.row[8]);
             //每列的信息 
         }   
    } 
    cout<<"+-----------+---------+------+-----+--------------------+------+-----------+-----------+"<<endl;
    End();
}

//****************************************************************************

//****************************************************************************



/*密码隐藏 的2个函数 */ 
// 1.改变终端设置  
int getch()
{
    int c=0;
    struct termios org_opts, new_opts;
    int res=0;
    
    //-----  store old settings -----------
    res=tcgetattr(STDIN_FILENO, &org_opts);//获取与终端相关的参数
    assert(res==0);
   
   //---- set new terminal parms --------
   memcpy(&new_opts, &org_opts, sizeof(new_opts));//拷贝结构体
 
   new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
   tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);//设置终端参数
   c=getchar();
   
   //------  restore old settings ---------
   res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);//还原终端设置
   assert(res==0);
   return c;
}

// 2.密码隐藏
char Passwd(char passwd[50])
{   
    
     int i;
    //cout<<"\t\t\033[33;32m 请输入密码: \033[0m";
    for(i=0;i<3;i++)   //最多隐藏?????个
    {
    for(i=0;;i++)
    {
      passwd[i]=getch();
      
      if(passwd[i]=='\n')
       {
         passwd[i]='\0';
         break;
       }
       
      if(passwd[i]==127)
       {
         printf("\b \b");
         i=i-2;
       }
       
      else
         printf("*");
      
      if(i<0)
       {
         passwd[0]='\0';
         //break;
       }
     }//for 2 

   } //for 1

   printf("\n");
}

//====================================================================

//精灵进程初始化
int init_daemon(void)
{

    pid_t pid;

    if((pid = fork()) < 0)
      return 0;
      
    else if (pid != 0)
      exit(0);
    /*parent goes bye-bye*/

    /*child continues*/
    setsid();
    /*become session leader*/

    chdir("/");
    /*change working directory*/
        
    umask(0);
    /*clear our file mode creation mask*/

}


//============================================

//关闭音乐播放
void Close_music()
{
    
}







