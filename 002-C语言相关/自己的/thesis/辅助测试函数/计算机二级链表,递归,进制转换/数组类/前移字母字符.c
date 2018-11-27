/*
函数fun的功能是:将形参s所指字符串中的所有字母字符顺序前移,其他字符顺序
后移,处理后将新字符串的首地址作为函数值返回
例如:若s所指字符串为:"asd123fgh543df" ,处理后新字符串为"asdfghdf123543
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *fun(char *s)
{
	int i,j,k,n;
	char *p,*t;
	n=strlen(s)+1;
	t=(char *)malloc(n*sizeof(char));
	p=(char *)malloc(n*sizeof(char));
	
	j=0;k=0;
	
	for(i=0;i<n;i++)
	{
		if(((s[i]>='a')&&(s[i]<='z'))||((s[i]>='A')&&(s[i]<='Z')))
		{
			t[j]=s[i];
			j++;
		}
		else
		{
			p[k]=s[i];
			k++;
		}
	}
	
	for(i=0;i<k;i++)
	{
		t[j+1]=p[i];
	}
	t[j+k]='\0';
	return t;	
}

int main()
{
	char s[80];
	printf("please input :");
	scanf("%s",s);
	printf("\nThe result is:%s\n",fun(s));
	return 0;
}











