#include<stdio.h>

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

typedef struct abc
{
	char a;
	int d;
	short c;
	char b;
}abc;
struct 
{
	char a;
	int d;
	short c;
	char b;
}dataAlign1;

struct 
{
	char a;
	char b;
	short c;
	int d;
}dataAlign2;

struct 
{
	char a;
	int d;
	short c;
	char b;
	abc e;
	char f;
	abc g;
	char i;
}libo;

int main()
{
	int *p = NULL;
	char *q = NULL;
	double *s = NULL;
	printf("sizeof(p) = %ld\n",sizeof(p));
	printf("sizeof(q) = %ld\n",sizeof(q));
	printf("sizeof(s) = %ld\n",sizeof(s));
	printf("sizeof(int) = %ld\n",sizeof(int));
	printf("sizeof(dataAlign1) = %ld\n",sizeof(dataAlign1));
	printf("sizeof(dataAlign2) = %ld\n",sizeof(dataAlign2));
	printf("sizeof(libo) = %ld\n",sizeof(libo));
	return 0;
}






