#include "data_client.h"

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

//模拟与服务器连接函数,动态打印>>
void dynamic_print()
{
	int i = 3;
	while(i)
	{
		printf(L_CYAN" >> >> "NONE);
		fflush(stdout);
		i--;
		usleep(500000);
	}
	printf("\n\n");
}
