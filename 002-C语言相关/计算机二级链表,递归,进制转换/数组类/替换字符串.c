/*
函数fun的功能是:将s所指的字符串中最后一次出现的与t1所指字符串相同的
子串替换成t2所指的字符串,所形成的新串放在w所指的数组中.要求t1和t2所指字符串
的长度相同.  例如:当s所指的字符串中的内容为"abcdababfabc" t1所指串中的内容为"ab",
t2所指子串中的内容为"99" 时,结果在w所指的数组中的内容应为abcdabf99c
*/

#include<stdio.h>
#include<string.h>

void fun(char *s,char *t1,char *t2,char *w)
{
	char *p,*r,*a;
	strcpy(w,s);
	
	while(*w)
	{
		p=w;//把当前位置的w赋值给p
		r=t1;
		while(*r)
		{
			if(*r==*p) //如果一样,r++,p++
			{
				r++;
				p++;
			}
			else      //否则跳出,继续使用当前的r的内容
			{
				break;
			}
		}
		if(*r=='\0')
			a=w;   //当r继续到内容为0时则说明找到一样的字符串了,纪录了相同字符的起始位置,更新a的位置为最后一个相同的字符串
		w++;       //将w移动到下一个位置与r的内容比较
	}
	r=t2;
	while(*r)  //从字符串相同位置处进行替换成t2的内容
	{
		*a=*r;
		a++;
		r++;
	}	
}

//此函数用来判断t1字符串在s中是否连续的存在,因为多个字符时是连续判断的
int judgeexist(char *a,char *b)
{
	char *h,*q,*p;
	int n = 0;
	h = a;
	while(*h)
	{
		p = h;
		q = b;
		while(*q != '\0')
		{
			if(*q == *h)
			{
				q ++;
				h ++;
			}
			else 
				break;
		}
		if(*q == '\0')
			return 1;
		h ++;
	}
	return 0;
}

int main()
{
	char s[100],t1[100],t2[100],w[100];
	printf("\nplease enter string s:");
	scanf("%s",s);
	
	printf("\nplease enter substring t1:");
	scanf("%s",t1);
	while(1)
	{
		if(!judgeexist(s,t1))
		{
			printf("字符串s中不存在对应的字符串t1!\n");
			printf("\nplease enter t1 again:");
			scanf("%s",t1);
		}
		else
			break;
	}
	
	printf("\nplease enter substring t2:");
	scanf("%s",t2);
	if(strlen(t1)==strlen(t2))
	{
		fun(s,t1,t2,w);
		printf("\nThe result is:%s\n",w);
	}
	else
	{
		printf("\nError :strlen(t1)!=strlen(t2)\n");
	}
	return 0;
}
















