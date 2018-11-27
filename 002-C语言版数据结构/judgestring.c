#include<stdio.h>


int check_com_cn(char *a,char *b)
{
	char *h,*q,*p;
	int n = 0;
	h = a;
	
	while(*h != '\0')
	{
		p = h;
		q = b;
		while(*q != '\0')
		{
			if(*q == *p)   //当有一个字符匹配了时，主串和子串同时往后移动一位，再进行比较
			{
				q ++;
				p ++;
			}
			else 
				break;   // 直到break，跳出循环时再比较是否为子串到达了结尾
		}
		if(*q == '\0')
			n ++;
		h ++; // 此时再从上一次第一个匹配的字符处开始加一，再次进行比较主串和子串
	}
	return n;
}

int main()
{
	char str[20] = "1c2o3mc4o5m";
	char s[5] = "com";
	char t[20] = "123concomcom";
	printf("%d \n\n\n\n\n",check_com_cn(str, s));
	printf("%d \n",check_com_cn(t, s));
	return 0;
}
