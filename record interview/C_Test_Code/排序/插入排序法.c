/*
用插入排序法对字符串中的字符串进行升序排序.插入法的基本思想是:先对头两个字符进行排序
,然后把第三个字符插入到前两个字符中,插入后前三个字符串依然有序;再把第四个字符插入到
前三个字符中.... 待排序的字符串已经在主函数中赋予
*/

#include<string.h>
#include<stdio.h>
#define N 80

void insert(char *aa)
{
	int i,j,n;char ch;
	n = strlen(aa);
	for(i = 1; i < n; i++)
	{
		ch = aa[i];
		j = i-1;
		while((j >= 0)&&(ch < aa[j]))
		{
			aa[j+1] = aa[j];
			j--;
		}
		aa[j+1] = ch;
	}
}

void main()
{
	char a[N] = "QWERTYUIOPASDFGHJKLNBVCXZ";
	printf("The original string :%s\n",a);
	insert(a);
	printf("The string after sorting: %s\n\n",a);
}




