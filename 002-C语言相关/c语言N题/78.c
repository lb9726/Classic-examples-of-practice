#include<stdio.h>
#include<stdlib.h>

int main()
{
	unsigned char *p1;
	unsigned long *p2;
	int *a;
	p1 = (unsigned char *)0x801000;
	p2 = (unsigned long *)0x810000;
	printf("unsigned long = %ld\n",sizeof(unsigned long));
	printf("unsigned char = %ld\n",sizeof(unsigned char));
	printf("p2 = %ld\n",sizeof(p2));
	printf("p1 = %ld\n",sizeof(p1));
	printf("a = %ld\n",sizeof(a));
	printf("p1+5 = %p\n",p1+5);
	printf("p2+5 = %p\n",p2+5);
	return 0;
}
