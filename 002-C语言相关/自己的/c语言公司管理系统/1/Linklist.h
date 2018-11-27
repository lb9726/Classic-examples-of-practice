#ifndef _LINKLIST_H
#define _LINKLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include<termios.h>
#include<unistd.h>
#include<assert.h>
//#include<string>

typedef struct PERSONINFO
{
    int id;                //人员编号
    char name[30];		   //人员姓名
    char sex[10];          //性别
    char passwd[30];       //密码
    char position[30];      //职称
    char department[20];   //部门
    char grade[10];        //等级
    char leader[30];       //上级
    double stasalary;      //固定工资
    int worktime;          //技术人员工作时间
    double timereward;     //单位时间工作的报酬
    double ticheng;        //销售部人员的提成
    double zonge;          //销售总额
    char performance[40];  //表现
    int latertimes;        //迟到次数
    double salary;         //最终工资
    char beizhu[100];      //备注
}PERSONINFO;

//员工信息结点
typedef struct _STNODE
{
    PERSONINFO person;
    struct _STNODE *next;
}STNODE;

typedef struct logmes
{
	int id;                  //登录人员的id编号
	char name[30];           //登录人员的姓名
	char passwd[30];         //登录人员的密码
	char lastlogintime[40];  //上次登录的时间
	int logincounts;         //登录次数
}LOGMES;

//登录人员信息结点
typedef struct STNODE1
{
    LOGMES person1;
    struct STNODE1 *next;
}STNODE1;

char stime1[30];           //系统时间
char checknum[10];          //生成的验证码
char SEX[10];               //性别
char POS[30];               //职称
char DEP[30];               //部门
char GRD[10];               //等级
char LEA[30];               //上级

// 等待键盘输入是一个数字0~1否则就一直等待用户输入
int inputdigit01(char ch);
// 等待键盘输入是一个数字0~2否则就一直等待用户输入
int inputdigit02(char ch);
// 等待键盘输入是一个数字1~2否则就一直等待用户输入
int inputdigit12(char ch);
// 等待键盘输入是一个数字0~3否则就一直等待用户输入
int inputdigit03(char ch);
// 等待键盘输入是一个数字0~5否则就一直等待用户输入
int inputdigit05(char ch);
// 等待键盘输入是一个数字0~6否则就一直等待用户输入
int inputdigit06(char ch);
// 等待键盘输入是一个数字0~8否则就一直等待用户输入
int inputdigit08(char ch);

int getch();

//密码隐藏函数
void hiden(char pd[30]);

//随机数生成验证码
void get_rand_str(int number);

//输入验证码调用函数
int iputchecking();
//模拟与服务器连接函数,动态打印>>
void printdot();
//性别选择
void chosex(int d);

//添加人员时的职称选择//由登录的人的职称限定他可以添加的人员信息
void chopos(char pos[30],int d);

//部门选择
void depart(PERSONINFO e);

//级别选择
void gradechoice(PERSONINFO e);

//上级选择
void leaderchoice(PERSONINFO e);

//固定工资
double stablesal(PERSONINFO e);

//工作时间
int wtime(PERSONINFO e);

//单位时间报酬
int treward(PERSONINFO e);

//提成
double tic(PERSONINFO e);

//读文件到链表的操作
STNODE * readfiletolist(char filename[30]);
//保存函数
void save(STNODE *head);

//生成最大编号
int readfileID(STNODE *head);

//销毁链表
void DestroyLinklist(STNODE *head);

//删除链表结点
STNODE * DeleteNode(STNODE *head,STNODE *q);

//返回主界面函数
void rethome();

//打印信息函数
void print(PERSONINFO person);

//按姓名查找
STNODE *findname(STNODE *head,char name[30],char pos[30]);

//按编号查找
STNODE *findID(STNODE *head,int bianhao,char pos[30]);

//按名字或编号删除调用的子函数
STNODE * findfordelete(STNODE *head,char pos[30]);

//按名字或编号查找的函数
STNODE * findformodify(STNODE *head,char pos[30]);

//添加人员信息
STNODE * AdddicinfoUI(STNODE *head,char pos[30]);

void savedeleteinfo(STNODE *p);

//删除人员信息
STNODE * deletedicinfo(STNODE *head,char pos[30]);

//修改人员信息函数
STNODE *Modifydicinfo(STNODE *head,char pos[30]);

//按名字或编号查找的函数
void searchnameorID(STNODE *head,char pos[30]);

void prit(STNODE *p);

//读文件并且打印数据的函数
void showdeleteinfo(char pos[30]);

//boss查看工资报表
void bossshowtable(STNODE *head);
//boss录入工资
STNODE * bossinputsalary(STNODE *head);

//技术人员或销售人员查看自己的信息
void showselfinfo(STNODE *head,int idnum);

//技术人员或销售人员修改自己的信息
STNODE *Modselfinfo(STNODE *head,int idnum);

//读文件并且打印数据的函数
void showdicinfo(STNODE *head,char pos[30]);

//退出前保存操作
void confirmsave(STNODE *head);

//获取当前系统时间
void gettime();

STNODE1 * readfiletolist1(char filename[30]);

void save1(STNODE1 *head);

//文件追加函数
void appentext(char filename[30],int id,char name[30],char pass[30],char last[30],int lotimes);

//登录时提示上次登录时间和登录次数,首次登录提示首次登录
void logininf(int id,char name[30],char pass[30]);
/*
//工资按照职称,表现,迟到次数计算最终工资
void judgesalary(PERSONINFO e);
*/
void judgesalary(STNODE *p);
#endif

























