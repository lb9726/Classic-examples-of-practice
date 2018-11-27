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

static int add_flag = 0;
static int delete_flag = 0;
static int modify_flag = 0;

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

typedef struct logmes
{
	char name[30];           //登录人员的姓名
	char passwd[30];         //登录人员的密码
	int logincounts;         //登录次数
	char lastlogintime[40];  //上次登录的时间
}LOGMES;

//登录人员信息结点
typedef struct Login_STNODE
{
    LOGMES person1;
    struct Login_STNODE *next;
}Login_STNODE;

//联系人信息节点
typedef struct STNODE
{
	PERSONINFO person;
	struct STNODE *next;
}STNODE;

int getch();

void hiden(char pd[30]);

char * get_rand_str(int number);

int iputchecking();

void printdot();

char * gettime();

void generate_node(PERSONINFO people,STNODE *head);

void copy_node(STNODE *p,STNODE *head);

int jugde_file_isEmpty(char filename[25]);



void read_file_use_fscanf(char filename[30],STNODE *head);

void * read_login_table(char filename[],Login_STNODE *head);

STNODE * readfiletolist(char filename[30]);

Login_STNODE * readfiletolist_for_login(char filename[30]);

void generate_node_for_login(LOGMES people,Login_STNODE *head);

void DestroyLinklist(STNODE *head);

void linksort_small_to_big(STNODE *head);

void linksort_big_to_small(STNODE *head);

void get_id_to_array(STNODE *head,int a[]);

void array_sort_small_to_big(int a[],int n);

int get_min_id(STNODE *head);

int inputdigit(char li,char left,char right);

void write_file(char filename[],LOGMES people);

void logininf(char name[30],char pass[30]);



STNODE * DeleteNode(STNODE *head,STNODE *temp);

void print_name_result(STNODE *head,int flag,int choice,char name[]);

void print_id_result(STNODE *head,int flag,int choice,int id);

STNODE *search_name_genratelinkst(STNODE *head,char pname[30],int *flag);

STNODE *search_id_genratelinkst(STNODE *head,int id,int *flag);

STNODE *findname(STNODE *head,char pname[30]);

STNODE *modify_id_info(STNODE *head,int id,int choice);

STNODE *findID(STNODE *head,int id);

void show_modify_id(STNODE *head,int id,int choice);

int show_modify_name(STNODE *head,char name[],int choice);

STNODE * dealwith_same_name(STNODE *head,int flagnum,char name[30]);

STNODE * findfordelete(STNODE *head);

void showinfo_use_three_kinds(STNODE *head);

void savedeleteinfo(STNODE *p);

void savefile(STNODE *head,char filename[30]);

void show_delete_person_info();

void youhua(char *p);

int judge_islegal(char *q);

void string_to_int(char str[]);

int return_len(char *p);

int return_int(char *p);

void age_legal(char str[]);

int check_com_cn(char *s,char *t);

void check_mails(char str[]);


int MyStrlen(char *p);

void InitAarry(char *name[],char *str[],int *length[],int a,int n);

void ReadInfotoArray(char *array[],int i,STNODE *head);

int GetLines(STNODE *head);

int AppendColumn(char *array[]);

char * int_form_string(int num);

void ShowInfo_In_order(STNODE *head);

void PrintInfoIntoTable(char *array[],char *str[],int max[],int a,int n);

void GainColumnMaxLength(char *array[],int *length[],int max[],int erwei[][9],int c,int n);

int GetMax(int erwei[][9],int *length[],int max[],int c,int n);

void AddBlank(char *array[], int *length[],int c,int n);

void linking(char *array[],char *str[],int a,int n);

void FreeSpace(char *name[],char *str[],int *length[],int a,int n);

#endif
