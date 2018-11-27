#include<stdio.h>
#include<stdlib.h>

typedef union
{
	long i;
	int k[5];
	char c;
}DATE;

struct data
{
	int cat;
	DATE cow;
	double dog;
}too;

DATE max;

struct test
{
	char a;
	int b;
}TEST;

int main()
{
	
	printf("sizeof(DATE) = %ld\n",sizeof(DATE));
	printf("sizeof(long) = %ld\n",sizeof(long));
	printf("long i = %p\n",&(max.i));
	printf("int k= %p\n",&(max.k));
	printf("char c = %p\n\n",&(max.c));
	
	printf("int cat = %p\n",&(too.cat));
	printf("DATE cow = %p\n",&(too.cow));
	printf("double dog = %p\n",&(too.dog));
	printf("sizeof(struct data) = %ld\n\n",sizeof(struct data));
	
	printf("sizeof(TEST) = %ld\n",sizeof(TEST));
	printf("char a = %p\n",&(TEST.a));
	printf("int b= %p\n",&(TEST.b));
	
	printf("sizeof(max) = %ld\n",sizeof(max));
	return 0;
}

