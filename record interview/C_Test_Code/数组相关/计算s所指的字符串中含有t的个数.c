/*
函数fun的功能:计算s所指字符串中含有t所指的字符串的数目,并作为函数值返回
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 80

int fun(char *s, char *t)
{
	int n;
	char *p,*r;
	n = 0;
	p = &s[0];
	r = t;
	
	while(*p)
	{
		if(*r == *p)
		{
			r++;
			if(*r == '\0')
			{
				n++;
				r = t;//r=&t[0];//当前的一轮比较完之后,r重新指向t的首地址进行下一轮比较
			}
		}
		p++;
	}
	return n;
}

//将fgets函数多存入的一个\n处理掉
void youhua(char *p)
{
	while(*p)
	{	if(*p =='\n')
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
	char a[N], b[N];
	int m;
	printf("\nplease enter string a:");
	fgets(a, N, stdin);//fgets函数会把\n也写入数组之中所以要处理\n  //gets(s);比gets多一个
	youhua(a);
	printf("\nplease enter substring b:");
	fgets(b, N, stdin);//fgets函数会把\n也写入数组之中所以要处理\n  //gets(s);比gets多一个
	youhua(b);
	m = fun(a, b);
	printf("\nThe result is :m = %d\n", m);
}










