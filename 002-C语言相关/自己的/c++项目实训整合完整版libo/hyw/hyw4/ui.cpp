#include "ui.h"

//登录界面
int Login() 
{
    int i=0;  //判断循环的输入错误
    int UserName;            //用户名（编号）
    char passwd[48];         // 密码隐藏
    char code[10]={'\0'};                 
    char str[5];             //验证码
    char password[10]="123"; //Boss
    int boss=10000;
      
    list<Employee> m;  //容器
    Employee em;
    list<Employee>::iterator ra=m.begin();  //it 迭代器
    
    DataBase db;
    string s;
    s="select *from user"; 
    db.initDB("localhost" , "root", "123" , "Company" );
    db.executeSQL(s);   //查询数据库
    db.res = mysql_store_result(db.connection);     //接受结果集
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
    cout<<"\t\t\033[33;32m     ***********************************      \n";
    cout<<"\t\t\033[33;32m*************欢迎登陆公司管理系统*************\033[0m\n\n";
    cout<<"\n\n\n";
    cout<<"\t\t\033[33;32m 请输入用户名： \033[0m";
    cin>>UserName;
   
    cout<<"\n";
    cout<<"\t\t\033[33;32m 请输入密码: \033[0m";
    Passwd(passwd); // 密码隐藏
    
    cout<<"\n";
    Verification_code(str);       //生成验证码
    cout<<"\n";
    cout<<"\t\t\033[33;32m 请输入验证码: \033[0m";
    cin>>code;
    
    cout<<"\n";
    cout<<"\t\t\033[33;32m loading... \033[0m\n";
    
    if((boss==UserName) && strcmp(password,passwd)==0 && strcmp(code,str)==0 )
    {
      return 1;
    }

    ra=m.begin();  // 定义ra迭代器重新指向开头（类似指针）
    while(ra!=m.end())  //
    {
      if((ra->m_Number==UserName) && strcmp(ra->m_passwd,passwd)==0 && strcmp(code,str)==0)  // 判断 用户名 密码 验证码
      {
     
        id=ra->m_Number;
        if(strcmp(ra->m_position,"经理")==0)
         {
          strcpy(str_name,"经理:");
          strcat(str_name,ra->m_Name);
          i++;   // 输入正确 循环内不为0
          return 2;
         } 
         
         if(strcmp(ra->m_position,"销售经理")==0)
         {
          strcpy(str_name,"经理:");
          strcat(str_name,ra->m_Name);
          i++;
          return 3;
         } 
         
         
         if(strcmp(ra->m_position,"兼职技术人员")==0)
         {
          strcpy(str_name,"兼职技术人员:");
          strcat(str_name,ra->m_Name);
          i++;
          return 4;
         } 
         
         if(strcmp(ra->m_position,"兼职销售人员")==0)
         {
          strcpy(str_name,"兼职销售人员:");
          strcat(str_name,ra->m_Name);
          i++;
          return 5;
         } 
     }    
      ra++;    //迭代器自加
   }//while
    
    if(i==0)  //判断循环的输入错误 要在循环外  // 输入错误 循环外 为0
    {
      return 6;
      
    }
    
}   
    
void BossUI()   //boss 操作界面
{
    int choice;
    while(1)
    {
    system("clear");
    cout<<"\t\t\033[34;32m     ***********************************      \n";
    cout<<"\t\t\033[34;32m***********欢迎BOSS登陆公司管理系统************\033[0m\n\n"; 
    cout<<"\n\n\n"; 
    cout<<"\t\t\033[34;32m     1.添加员工             2.删除员工    \033[0m\n\n";
    cout<<"\t\t\033[34;32m     3.查看员工             4.修改员工    \033[0m\n\n";
    cout<<"\t\t\033[34;32m     5.查询员工             0.退出        \033[0m\n\n";
    cout<<"\t\t\033[34;32m 请输入你的选择： \033[0m";
    cin>>choice;
    Boss boss;
    switch(choice)
    {
          case 0:
                    //关闭音乐播放 kill ID
		    char S[48];
		    char buff[48];
		    FILE *fp;
		    fp=fopen("2.txt","r");
		    fgets(buff,6,fp);
		    //printf("%s\n",buff);
		    //fp=fopen("2.txt","w");  //清空重定向文件的内容
		    fclose(fp);
		    fp=NULL;

		    int i;
		    i=(buff[1]-48)*1000 +(buff[2]-48)*100 + (buff[3]-48)*10 + (buff[4]-48); 
		    //printf("%d\n",i);
		    sprintf(S,"kill %d",i);
		    system(S);
                 exit(0);
          case 1:
                 boss.Add();
                 break;
          case 2:
                 boss.Delete();
                 break;
          case 3:
                 boss.Show();
                 break;
          case 4:
                 boss.Change();
                 break;  
          case 5:
                 boss.Search();
                 break;
          default:
                 cout<<"\t\t\033[33;32m 您的输入有误!  请重新输入! \033[0m";
                 cout<<"\t\t\033[33;32m Press Any key to continue ... \033[0m";
                 cout<<'\t'<<'\n';
                 cout<<'\t';
                 while(getchar()!='\n');
                 getchar();
                 break;   
        }

   } 
    
}



void ManagerUI()   //经理操作界面
{
    int choice;
    
    while(1)
    {
    
    system("clear");
    cout<<"\t\t\033[34;32m     *************************************      \n";
    printf("\t\t\033[34;32m***********欢迎%s登陆公司管理系统************\033[0m\n\n\n",str_name);
    cout<<"\n\n\n";  
    cout<<"\t\t\033[34;32m     1.显示部门员工         2.添加员工    \033[0m\n\n";
    cout<<"\t\t\033[34;32m     3.查找员工             4.修改员工    \033[0m\n\n";
    cout<<"\t\t\033[34;32m     5.删除员工             6.查看个人信息       \033[0m\n\n";
    cout<<"\t\t\033[34;32m     7.修改密码             0.退出\033[0m\n\n";
    cout<<"\t\t\033[34;32m 请输入你的选择： \033[0m";
    cin>>choice;
    Manager manager;
    switch(choice)
    {
          case 0:
                  //关闭音乐播放 kill ID
		    char S[48];
		    char buff[48];
		    FILE *fp;
		    fp=fopen("2.txt","r");
		    fgets(buff,6,fp);
		    //printf("%s\n",buff);
		    //fp=fopen("2.txt","w");  //清空重定向文件的内容
		    fclose(fp);
		    fp=NULL;

		    int i;
		    i=(buff[1]-48)*1000 +(buff[2]-48)*100 + (buff[3]-48)*10 + (buff[4]-48); 
		    //printf("%d\n",i);
		    sprintf(S,"kill %d",i);
		    system(S);
                 exit(0);
          case 1:
                 manager.Show();
                 break;
          case 2: 
                 manager.Add();
                 break;
          case 3:
                 manager.Search();
                 break;
          case 4:
                 manager.Change();
                 break;  
          case 5:
                 manager.Delete();
                 break;
          case 6:
                 manager.Showown(id);
                 break;
          case 7:
                 manager.Chpasswd(id);
                 break;
          default:
                 break;
                 
    }
    
   } 
   
}


void Sell_ManagerUI()   //销售经理 操作界面
{
    int choice;
    
    while(1)
    {
    system("clear");
    cout<<"\t\t\033[34;32m     ****************************************      \n";
    printf("\t\t\033[34;32m************欢迎%s登陆公司管理系统************\033[0m\n\n\n",str_name); 
    cout<<"\t\t\033[34;32m     1.显示部门员工         2.添加员工    \033[0m\n\n";
    cout<<"\t\t\033[34;32m     3.查找员工             4.修改员工    \033[0m\n\n";
    cout<<"\t\t\033[34;32m     5.删除员工             6.查看个人信息\033[0m\n\n";
    cout<<"\t\t\033[34;32m     7.更改密码             0.退出\033[0m\n\n";
    cout<<"\t\t\033[34;32m 请输入你的选择： \033[0m";
    cin>>choice;
    Sell_manager sell_manager;
    switch(choice)
    {
          case 0:
                  //关闭音乐播放 kill ID
		    char S[48];
		    char buff[48];
		    FILE *fp;
		    fp=fopen("2.txt","r");
		    fgets(buff,6,fp);
		    //printf("%s\n",buff);
		    //fp=fopen("2.txt","w");  //清空重定向文件的内容
		    fclose(fp);
		    fp=NULL;

		    int i;
		    i=(buff[1]-48)*1000 +(buff[2]-48)*100 + (buff[3]-48)*10 + (buff[4]-48); 
		    //printf("%d\n",i);
		    sprintf(S,"kill %d",i);
		    system(S);
                 exit(0);
          case 1:
                 sell_manager.Show();
                 break;
          case 2: 
                 sell_manager.Add();
                 break;
          case 3:
                 sell_manager.Search();
                 break;
          case 4:
                 sell_manager.Change();
                 break;  
          case 5:
                 sell_manager.Delete();
                 break;
          case 6:
                 sell_manager.Showown(id);
                 break;
          case 7:
                 sell_manager.Chpasswd(id);
                 break;
          default:
                 break;
    }
    
   } 
    
}



void EmployeeUI()   //员工操作界面
{
    int choice;
    
    while(1)
    {
    
    system("clear");
    cout<<"\t\t\033[34;32m     ***********************************************      \n";
    printf("\t\t\033[34;32m************欢迎%s登陆公司管理系统************\033[0m\n\n\n",str_name);  
    cout<<"\t\t\033[34;32m     1.查看个人信息                2.修改密码       \033[0m\n\n";
    cout<<"\t\t\033[34;32m     0.退出                                       \033[0m\n\n";
    cout<<"\t\t\033[34;32m 请输入你的选择： \033[0m";
    cin>>choice;
    Sale_people sale_people;
    switch(choice)
    {
           case 0:
                   //关闭音乐播放 kill ID
		    char S[48];
		    char buff[48];
		    FILE *fp;
		    fp=fopen("2.txt","r");
		    fgets(buff,6,fp);
		  //printf("%s\n",buff);
		    //fp=fopen("2.txt","w");  //清空重定向文件的内容
		    fclose(fp);
		    fp=NULL;

		    int i;
		    i=(buff[1]-48)*1000 +(buff[2]-48)*100 + (buff[3]-48)*10 + (buff[4]-48); 
		  //printf("%d\n",i);
		    sprintf(S,"kill %d",i);
		    system(S);
		    
                 exit(0);
           case 1:
                 sale_people.Showown(id);
                 break;
           case 2:
                 sale_people.Chpasswd(id);
                 break;
           default:
                 break;
                 
    }
    
   } 
    
}












