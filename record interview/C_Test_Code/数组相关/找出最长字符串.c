/*
下列给定程序中函数fun的功能是:从N个字符串中找出最长的串
,并将地址作为函数返回值返回.各个字符串在主函数中输入,并
放入一个字符串数组中.
*/

#include<stdio.h>
#include<string.h>
#define N 5
#define M 81
char *fun(char (*sq)[M])
{
	int i;
	char *sp;
	sp = sq[0];
	for(i = 0; i < N; i++)
	{	
	    if(strlen(sp) < strlen(sq[i]))
		{	
		    sp = sq[i];
		}
    }
	return sp;
}

void main()
{
	char str[N][M], *longest;
	int i;
	printf("Enter %d lines:\n", N);
	
	for(i = 0; i < N; i++)
	{
		gets(str[i]);
    }
	printf("\nThe %d string :\n", N);
	for(i = 0; i < N; i++)
	{
	   	puts(str[i]);
	}
	longest = fun(str);
	printf("\n The longest string :\n");
	puts(longest);
}














