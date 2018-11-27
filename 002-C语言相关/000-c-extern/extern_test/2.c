#include<stdio.h>
#include<stdlib.h>

//将fgets函数多存入的一个\n处理掉
void you_hua(char *p)
{
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

void enter_string(char str[80])
{
    fgets(str, 79, stdin);
}
