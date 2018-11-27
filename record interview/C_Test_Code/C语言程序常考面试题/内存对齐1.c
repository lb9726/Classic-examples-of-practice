#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>

typedef struct A
{
	char t;
	char k;
	unsigned short i;
	unsigned long m;
} A;

void Test_strlen_types()
{
	printf("sizeof(char) = %ld\n",sizeof(char));
	printf("sizeof(short) = %ld\n",sizeof(short));
	printf("sizeof(int) = %ld\n",sizeof(int));
	printf("sizeof(float) = %ld\n",sizeof(float));
	printf("sizeof(double) = %ld\n",sizeof(double));
	printf("sizeof(long) = %ld\n",sizeof(long));
	printf("sizeof(char *) = %ld\n",sizeof(char *));
	printf("sizeof(int *) = %ld\n",sizeof(int *));
}

int main()
{
	Test_strlen_types();
	printf("\n");
	printf("sizeof(A) = %ld\n", sizeof(A));
	return 0;
}
