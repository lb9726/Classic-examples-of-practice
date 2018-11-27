#ifndef _DATA_H
#define _DATA_H
#include<fstream>
#include<iostream>
#include<string>
#include<iomanip>

#include<stdlib.h>
#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>

#include <ctype.h>
#include <time.h>
#include<list>
#define N 20
#include<mysql/mysql.h> //ENGIN = Innodb default charset = utf8; 这是不带原子事件的
using namespace std;

extern MYSQL *conn;
extern MYSQL_RES *res;
extern MYSQL_ROW row;


class employee
{
public:
    int id;              //编号
    char name[20];       //姓名
    char passwd[20];     //密码
    char sex[10];         //性别
    char position[40];   //职称
    char department[10]; //部门
    char grade[6];       //等级
    char leader[20];     //上级
    double stablesalary; //固定工资
    int worktime;        //工作时间
    int timereward;      //单位时间报酬
    double ticheng;      //提成
    double zonge;        //销售总额
    char performance[40];//工作表现
    int latertimes;      //迟到次数
    double salary;       //工资
    int jifen;           //积分(用来提升等级)
    char beizhu[100];	 //工资备注

};
//改变终端设置
int getch();
//密码隐藏
void hiden(char pd[30]);
//验证码
void get_rand_str(int number);

//链接数据库
void connectdatabase();
//数据库按编号查找
int findnumber(char buf[200],int idum);
//数据库按姓名查找
int findname(char buf[200],char name[30]);
//按部门删除的查找
void showfordep();
//数据库按编号删除
void deletenumber(char buf,int idnum);
//数据库按编号删除
void deletename(char buf,char name[30]);
//boss按编号修改
void modifyid(char name[30],int idnum,int id,char pos[30],char dep[30],char gra[30],char lea[30],char perf[20],int ltime);
//boss按姓名修改
void modifyname(char name[30],char nname[30],int id,char pos[30],char dep[30],char gra[30],char lea[30],char perf[20],int ltime);
//经理销售经理按编号修改
void modifyid1(char name[30],int idnum,int id,/*char pos[30],char dep[30],char gra[30],char lea[30],*/char perf[20],int ltime);
//经理销售经理按姓名修改
void modifyname1(char name[30],char nname[30],int id,/*char pos[30],char dep[30],char gra[30],char lea[30],*/char perf[20],int ltime);
//boss按编号输入
void input1(char buf,int idnum);
//boss按姓名输入
void input2(char buf,char name[30]);
//经理销售经理按编号输入
void input3(char buf,int idnum);
//经理销售经理按姓名输入
void input4(char buf,char name[30]);
//部门选择
employee depart(employee e);

//级别选择
employee gradechoice(employee e);
//上级选择
employee leaderchoice(employee e);
//固定工资
employee stablesal(employee e);
//工作时间
int wtime(employee e,int worktime);
//单位时间报酬
int treward(employee e);

//提成
double tic(employee e);
//积分初始化
int jifeninit(employee e);

// 等待键盘输入是一个数字0~1否则就一直等待用户输入
int inputdigit01(char ch);

// 等待键盘输入是一个数字0~9否则就一直等待用户输入
int inputdigit12(char ch);
// 等待键盘输入是一个数字0~5否则就一直等待用户输入
int inputdigit05(char ch);
// 等待键盘输入是一个数字0~9否则就一直等待用户输入
int inputdigit02(char ch);

// 等待键盘输入是一个数字0~9否则就一直等待用户输入
int inputdigit09(char ch);

//模拟连接函数,动态打印>>
void printdot();
//模拟与服务器连接函数,动态打印点
void printdot1();
//向数据库发送sql语句
void sendrequest(char man[200]);
//工资按照等级判断
void judgesalary(employee e,int idnum);

//登录时显示上次登录时间函数并且将本次登录时间和次数写进数据库里面去
void logininf(int idnum,char name[30],char pass[30]);
class BOSS
{
public:
    BOSS(){};//构造函数
    void bossadd();         //添加人员信息
    void bossdel();         //删除人员信息
    void bossmod();         //修改人员信息
    void bossmodifypasswd();//修改人员密码
    void bosslook();        //查找人员信息
    void bossshow();        //显示人员信息
    void bossdeldeprt();//按部门删除人员信息
    void bossinputsalary(); //boss录入工资
    void bossshowtable();   //boss生成工资报表

};


//经理类,继承雇员类,拥有自己的成员固定工资
class Manager:public employee
{
public:
    Manager(){};//构造函数
    void add();    //添加人员信息
    void del();    //删除人员信息
    void mod();    //修改人员信息
    void managermodifypasswd();
    void look();   //查找人员信息
    void showposition();   //按职称显示人员信息
    void showdepartment();  //按部门显示人员信息
protected:
    //double stablesalary;//固定工资

};
//销售经理,继承雇员类,拥有自己的成员提成
class Salemanager:public employee
{
public:
    Salemanager(){};//构造函数
    void add();    //添加人员信息
    void del();    //删除人员信息
    void mod();    //修改人员信息
    void Salemodifypasswd();
    void look();   //查找人员信息
    void showposition();   //按职称显示人员信息
    void showdepartment(); //按部门显示人员信息
};


//销售人员类,继承雇员类,拥有自己的成员按提成分工资
class Saleperson:public employee 
{
public:
    Saleperson(){};//构造函数
    void show(int idnum);     //显示人员信息
};

//技术人员,继承雇员类,拥有自己的成员按时间算工资
class Skillperson:public employee
{
public:
    Skillperson(){};//构造函数
    void show(int idnum);  //显示人员信息
};

//各类用户都可以修改密码包括boss
void modifypasswd(int idnum);
#endif










