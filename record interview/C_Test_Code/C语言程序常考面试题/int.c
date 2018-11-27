#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>

int main()
{
	int a = 4;
	int b = 5;
	printf("&a = %p\n", &a);
	printf("&b = %p\n", &b);
	return 0;
}

/*
&a = 0x7fff4a139be8
&b = 0x7fff4a139bec
相差为4
*/
