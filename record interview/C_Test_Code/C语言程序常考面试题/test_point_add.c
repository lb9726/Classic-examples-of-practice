#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	unsigned char *p1;
	unsigned long *p2;
	p1 = (unsigned char *)0x801000;
	p2 = (unsigned long *)0x810000;
	printf("before p1 = %p\n", p1);
	p1 = p1 + 5;
	printf("after p1 = %p\n", p1);
	printf("before p2 = %p\n", p2);
	p2 = p2 + 5;
	printf("after p2 = %p\n", p2);
}

