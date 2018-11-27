#ifndef _ADDRDATA_H
#define _ADDRDATA_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include<termios.h>
#include<unistd.h>
#include<assert.h>
#include<malloc.h>

//int flag = 0;

typedef struct PERSONINFO
{
    int id;                //编号
    char name[30];		   //姓名
    char sex[10];          //性别
    char age[10];          //年龄
    char telephone[20];    //联系电话
    char address[60];      //家庭住址
    char group[40];        //群组
    char mails[60];        //邮箱
    char addtime[50];      //添加信息日期
}PERSONINFO;

typedef struct STNODE
{
	PERSONINFO person;
	struct STNODE *next;
}STNODE;

char * gettime();

void generate_node(PERSONINFO people,STNODE *head);

void copy_node(STNODE *p,STNODE *head);

void read_file_use_fscanf(char filename[30],STNODE *head);

STNODE * readfiletolist(char filename[30]);

void savefile(STNODE *head,char filename[30]);

void DestroyLinklist(STNODE *head);

void linksort_small_to_big(STNODE *head);

void linksort_big_to_small(STNODE *head);

void get_id_to_array(STNODE *head,int a[]);

void array_sort_small_to_big(int a[],int n);

int get_min_id(STNODE *head);

int inputdigit(char li,char left,char right);

STNODE * DeleteNode(STNODE *head,STNODE *temp);

void savedeleteinfo(STNODE *p);

int MyStrlen(char *p);

void InitAarry(char *name[],char *str[],int *length[],int a,int n);

void ReadInfotoArray(char *array[],int i,STNODE *head);

int GetLines(STNODE *head);

int AppendColumn(char *array[]);

void generate_node(PERSONINFO people,STNODE *head);

void read_file_use_fscanf(char filename[30],STNODE *head);

STNODE * readfiletolist(char filename[30]);

char * int_form_string(int num);

void ShowInfo_In_order(STNODE *head);

void PrintInfoIntoTable(char *array[],char *str[],int max[],int a,int n);

void GainColumnMaxLength(char *array[],int *length[],int max[],int erwei[][9],int c,int n);

int GetMax(int erwei[][9],int *length[],int max[],int c,int n);

void AddBlank(char *array[], int *length[],int c,int n);

void linking(char *array[],char *str[],int a,int n);

void FreeSpace(char *name[],char *str[],int *length[],int a,int n);

#endif
