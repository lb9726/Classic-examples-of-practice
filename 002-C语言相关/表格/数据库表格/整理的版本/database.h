#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct _WORKERS
{
    char Name[64];       //姓名
	char Num[20];        //编号
    char Sex[48];        //性别 male female
	char  Age[20];       //年龄
    char Rank[20];       //级别  2 3 4 5
    char Department[48]; //部门
    char Salary[30];     //当月薪水
	char Passwd[40];     //密码  
}WORKERS;

int MyStrlen(char *p);

void InitAarry(char *name[],char *str[],int *length[],int a,int n);

void ReadInfotoArray(char *array[],int i);

int GetLines(char filename[30]);

int AppendColumn(char *array[]);

void DefineAarryandStorageInfo();

//void PrintInfo(char *array[],int a,int n);

void PrintInfoIntoTable(char *array[],char *str[],int max[],int a,int n);

void GainColumnMaxLength(char *array[],int *length[],int max[],int erwei[][8],int c,int n);

int GetMax(int erwei[][8],int *length[],int max[],int c,int n);

void AddBlank(char *array[], int *length[],int c,int n);

void linking(char *array[],char *str[],int a,int n);

void FreeSpace(char *name[],char *str[],int *length[],int a,int n);

