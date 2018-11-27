#include<stdio.h>
int main()
{
	int a = 0x12345678;
	char *p;
	p = (char *) (&a);
	if( *p == 0x78)
	{
		printf("The little endian\n"); //小端模式
	}
	else
	{
		printf("The big endian\n"); // 大端模式
	}
	return 0;
}
