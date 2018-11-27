#ifndef _TABLE_H
#define _TABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct PERSONINFO
{
    int id;                //人员编号
    char name[30];		   //人员姓名
    char sex[10];          //性别
//    char passwd[30];       //密码
    char position[30];      //职称
 //   char department[20];   //部门
    char grade[10];        //等级
//    char leader[30];       //上级
//    double stasalary;      //固定工资
//    int worktime;          //技术人员工作时间
//   double timereward;     //单位时间工作的报酬
//    double ticheng;        //销售部人员的提成
//    double zonge;          //销售总额
//    char performance[40];  //表现
//    int latertimes;        //迟到次数
//    double salary;         //最终工资
//    char beizhu[100];      //备注
}PERSONINFO;

void readfile(char name[30]);

#endif
