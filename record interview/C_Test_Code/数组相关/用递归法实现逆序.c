#include<stdio.h>
#include<string.h>
void fun(char *a)
{
	if(*a)
	{
		fun(a+1);
		printf("%c",*a);
	}
}
/*
int main()
{
	char s[10] = "abcdefgh";
	printf("处理前字符串  = %s\n处理后的字符串 = ",s);
	fun(s);
	printf("\n");
	return 0;
}
*/

//将fgets函数多存入的一个\n处理掉
void youhua(char *p)
{
	while(*p)
	{	if(*p == '\n')
		{
		 	*p = '\0';
		 	break;
		}	
		p++;
	}
	return;
}


int main()
{
	char s[50];
	fgets(s, 50, stdin);//fgets函数会把\n也写入数组之中所以要处理\n  //gets(s);比gets多一个
	
	//int i; i = strlen(s);
	//printf("i = %d\n",i);
	youhua(s);
	printf("处理前字符串  = %s\n处理后的字符串 = ",s);
	fun(s);
	printf("\n");
	return 0;
}



