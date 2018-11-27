#ifndef _DATA_H
#define _DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  PRINTF1 printf("\t%-14s %-14s %-14s %-14s %-14s %-14s %-14s\n","员工姓名","员工编号","员工性别","员工年龄","员工级别","员工部门","员工工资");
/*
*职工信息
*/
typedef struct _WORKERS
{
    char Name[64];       //姓名
	int Num;             //编号
    char Sex[48];        //性别 male female
	int  Age;            //年龄
    int Rank;            //级别  2 3 4 5
    char Department[48]; //部门
    float Salary;        //当月薪水
	char Passwd[40];     //密码
	float Ticheng;	     //提成    
}WORKERS;

/**
* 职工信息结点
**/
typedef struct _NODE
{
	WORKERS worker;
	struct _NODE *next;
}NODE;

static NODE WorkerHead;


int AddWorkerNode(WORKERS worker);             //添加员工信息
void sort();                                   //排序
void CoverWorkerNode();                        //遍历员工信息
void ChangeWorkerNode(WORKERS worker);         //更改员工信息
void DeleteWorkerNode(WORKERS worker);         //删除员工信息
void SaveWorkerNode(WORKERS worker);           //保存员工信息
void DestroyLinklist();                        //销毁链表(砍头法)
void ReadWorkerNode(WORKERS worker);           //读取员工信息
void SeekWorkerNode(WORKERS worker);           //查找员工信息
int JudgeLogin(char user[40],char pass[40]);   //用户名 密码 判定
int CompareWorkerRank(int rank);               //级别比较

void ShowJZData(int num);                      //4-兼职技术人员，5-兼职推销员  
                                               //显示个人信息
void ChangeJZData(int num);                    //更改个人信息

void ManagerShow(WORKERS worker);              //2-经理 操作
                                               //显示 级别 4-兼职技术人员的信息

void XSManagerShow(WORKERS worker);            //3-销售经理 操作 
                                               //显示 级别 5-兼职推销员的信息

#endif




