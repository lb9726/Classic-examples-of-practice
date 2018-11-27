#include<stdio.h>
#include<stdlib.h>

struct name2
{
	char str;
	int num;
	short x;
};

int main()
{
	struct name2 y;
	printf("str = %p\n",&(y.str));
	printf("num = %p\n",&(y.num));
	printf("x = %p\n",&(y.x));
	printf("sizeof(short) = %ld\n",sizeof(short));
	printf("y = %ld\n",sizeof(y));
	return 0;
}
