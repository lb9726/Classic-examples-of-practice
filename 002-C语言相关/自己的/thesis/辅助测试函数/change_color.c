#include<stdio.h>
#include<stdlib.h>

#define NONE "\033[m" 
#define RED "\033[0;32;31m" 
#define GREEN "\033[0;32;32m" 
#define BLUE "\033[0;32;34m" 
#define YELLOW "\033[1;33m" 
 
#define LIGHT_RED "\033[1;31m" 
#define LIGHT_GREEN "\033[1;32m" 
#define LIGHT_BLUE "\033[1;34m"

int main()
{
	printf(RED "我是谁 \n" NONE);
	printf(GREEN "我是谁 \n" NONE);
	printf(BLUE "我是谁 \n" NONE);
	printf(YELLOW "我是谁 \n" NONE);
	printf(LIGHT_RED "我是谁 \n" NONE);
	printf(LIGHT_GREEN "我是谁 \n" NONE);
	printf(LIGHT_BLUE "我是谁 \n" NONE);
	printf("函数是%s()\n", __PRETTY_FUNCTION__);
	return 0;
}
