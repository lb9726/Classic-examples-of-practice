#include<stdio.h>
#include<stdlib.h>

//将fgets函数多存入的一个\n处理掉
void youhua(char *p)
{//printf("youhua = %s\n",p);
	while(*p != '\0')
	{	
		if(*p == '\n')
		{
		 	*p ='\0';
		 	break;
		}	
		p++;
	}
	return;
}

//判断出现非法字符串
int judge_islegal(char *q)
{
	int flag = 0;printf("judge_islegal = %s\n",q);
	int len = 0;
	char *p = q;
	if(*p == '\0')
	{	
		flag = 1;
		return flag ;
	}
	while(*q != '\0')
	{
		
		if(*q >='0' && *q <= '9')
		{
			flag = 0;
			
		}
		else
		{
			
			flag = 1;
			return flag;
		}
		q++;
	}
	return flag;
}

int return_int(char *p)
{
	int num = 0;//printf("p = %s\n",p);
	while(*p!= '\0')
	{
		num = num*10 + *p-'0';
		p++;
	}
	return num;
}

int string_to_int()
{
	char str[50];
	int id = 0;
	printf("请输入数字！！\n");
	do
	{
		fgets(str,40,stdin);
		youhua(str);
		if(judge_islegal(str))
		{
			printf("不能包含数字以外的字符，请重新输入!!!\n");
			
		}
	}while(judge_islegal(str));
	id = return_int(str);
	
}

int main()
{	
	printf("num = %d\n",string_to_int());
	return 0;
}
