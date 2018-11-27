#ifndef _FORMATPRINTF_H
#define _FORMATPRINTF_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

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

//联系人信息节点
typedef struct STNODE
{
    PERSONINFO person;
    struct STNODE *next;
}STNODE;

#define NONE "\e[0m"
#define BLACK "\e[0;30m"
#define L_BLACK "\e[1;30m"
#define RED "\e[0;31m"
#define L_RED "\e[1;31m"
#define GREEN "\e[0;32m"
#define L_GREEN "\e[1;32m"
#define BROWN "\e[0;33m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[0;34m"
#define L_BLUE "\e[1;34m"
#define PURPLE "\e[0;35m"
#define L_PURPLE "\e[1;35m"
#define CYAN "\e[0;36m"
#define L_CYAN "\e[1;36m"
#define GRAY "\e[0;37m"
#define WHITE "\e[1;37m"

#define BOLD "\e[1m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define REVERSE "\e[7m"
#define HIDE "\e[8m"
#define CLEAR "\e[2J"
#define CLRLINE "\r\e[K" //or "\e[1K\r"

int myStrLen(char *p);

void initAarry(char *name[], char *str[], int *length[], int a, int n);

void showInfoInorder(STNODE *head);

int getLines(STNODE *head);

int appendColumn(char *array[]);

void generateNode(PERSONINFO people, STNODE *head);

void readFileUseFscanf(char filename[30], STNODE *head);

STNODE * readFileToList(char filename[30]);

char * intFormString(int num);

void readInfoToArray(char *array[], int i, STNODE *head);

void gainColumnMaxLength(char *array[], int *length[], int max[], int erwei[][9], int c, int n);

int getMax(int erwei[][9], int *length[], int max[], int c, int n);

void addBlank(char *array[], int *length[], int c, int n);

void linking(char *array[], char *str[], int a, int n);

void printInfoIntoTable(char *array[], char *str[], int max[], int a, int n);

void destroyLinklist(STNODE *head);

void freeSpace(char *name[], char *str[], int *length[], int a, int n);

#endif



