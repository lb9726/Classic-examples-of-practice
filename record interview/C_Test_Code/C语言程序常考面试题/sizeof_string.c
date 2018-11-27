#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char str[] = "hello";
	char *p = str;
	int n = 3;
	printf("sizeof(str[]) = %ld\n",sizeof(str));
	printf("sizeof(p) = %ld\n",sizeof(p));
	printf("sizeof(int n) = %ld\n",sizeof(n));
}
