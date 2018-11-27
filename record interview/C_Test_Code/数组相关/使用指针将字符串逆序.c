#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 50

//将fgets函数多存入的一个\n处理掉
void youhua(char *p)
{
	while(*p)
	{	
		if(*p == '\n')
		{
		 	*p = '\0';
		 	break;
		}	
		p++;
	}
	return;
}

//将字符串逆置
void reserve(char *q)
{
	char *s, *t, ch;
	s = t = q;
	while(*s)
	{
		s++;
	}
	s--;
	while(t <= s)
	{
		ch = *t;
		*t = *s;
		*s = ch;
		t++;
		s--;
	}
}

void print(char *a)
{
	while(*a)
	{
		printf("%c", *a);
		a++;
	}
	printf("\n");
}
int main()
{
	char s[N];
	printf("请输入字符串:");
	fgets(s, N, stdin);
	youhua(s);
	reserve(s);
	printf("逆序后字符串:");
	print(s);
	return 0;	
}












