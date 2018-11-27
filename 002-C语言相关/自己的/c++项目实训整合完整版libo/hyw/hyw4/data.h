#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <mysql/mysql.h>
#include <iomanip>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <list>
#include <errno.h>

#include<termios.h>  //密码隐藏
#include<assert.h>

#include<fcntl.h>// open  
#include<sys/types.h>  
#include<sys/stat.h>
#include<time.h>

 
using namespace std;


//函数声明


//类的定义
class DataBase   // 数据库类
{
public:
    DataBase();  //构造函数
    bool initDB(string server_host , string user, string password, string db_name);  //初始化  server_host="localhost"
    
    bool executeSQL(string sql_str);  //执行SQL语句
    
    bool execute_select_SQL(string select_sql_str); //执行SQL select语句
    ~DataBase();  //析构函数
    MYSQL *connection;  //MYSQL链接指针
    MYSQL_RES *res;     //结果集指针
    MYSQL_ROW row;      //行 内容  将列表输出转化为行输出
};

class Boss
{
  public:
    void Add();                   //添加员工信息   
    void Delete();                //删除员工
    void Change();                //更改信息
    void Search();                //查询员工信息
    void Show();                   //显示所有员工
    DataBase db;
};
class Emaction
{   
       
    public:
      DataBase db;
      void Showown(int id);
      void Chpasswd(int id);      
};
//int Emaction::number=0;
class Employee  //员工类
{
public:
    int  m_Number;            //编号
    char m_Name[48];          //姓名
    int  m_age;               //年龄
    char m_sex[48];           //性别
    char m_position[48];      //职称
    int  m_level;             //级别
    int  m_salary;            //薪水
    char m_passwd[48];        //密码
    char m_Tel[40];           //电话
};


class Manager:public Employee,public Emaction //经理类
{
private:
	float m_fixed_salary;   //固定薪资
	DataBase db;
public:
	void Add();                   //添加员工信息   
        void Delete();                //删除员工
        void Change();                //更改信息
        void Search();                //查询员工信息
        void Show();                   //显示所有员工
        void Salary_calculation();  //经理工资计算
};


class Sale_people:public Employee,public Emaction   //销售人员类
{
private:
    float m_sale_commission_salary;  //提成工资         
    DataBase db;
};


//销售经理类  虚继承 继承 经理和销售人员
class Sell_manager:public Emaction   
{
private:
        float m_fixed_salary;       //固定薪资
        float m_commission_salary;  //提成工资
        
public:
        DataBase db;
	void Add();        
        void Delete();     
        void Change();     
        void Search();   
        void Show();  	
     //   void Salary_calculation();  //销售经理工资计算

};




class Technology_people:public Employee,public Emaction   //技术人员类
{
private:
        float m_hour_salary;   //计时工资

public:   
      DataBase db;
      
      //  void Salary_calculation();  //工资计算
};


int Max(list<Employee>m);
char Verification_code( char str[5]);  //char str[5]; 获取五位的随机串
void BossUI();    //boss 操作界面
int Login();     //登录界面
void ManagerUI();        //经理操作界面
void Sell_ManagerUI();   //销售经理操作界面
void EmployeeUI();       //员工操作界面
void End();
char *Gaintime(char *q);
static char str_name[50]; //静态全局 用户名变量
void *clocktime();
static int id;



//隐藏密码声明
char Passwd(char passwd[50]);// 密码隐藏
int getch();  //改变终端设置 

int init_daemon(void);  //精灵进程初始化

void Close_music();     //关闭音乐播放

#endif











