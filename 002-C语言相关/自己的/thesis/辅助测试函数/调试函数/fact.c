#include <stdio.h>
#include <stdlib.h>
 
#include "my_debug.h"
 
int fact(int n)
{
	int i, f = 1;
	for( i=1; i<=n; i++)
	{
		f *= i;
		my_debug(MY_SECTION_FACT, 250)("i=%d ; f=%d\n", i, f);
	}
	return f;
}
 
int main(int argc, char *argv[])
{
	if ( argc < 2 )
	{
		my_init_debug_levels(MY_SECTION_FACT, 0);
	}
	else
	{
		my_init_debug_levels(MY_SECTION_FACT, atoi(argv[1]));
	}
	printf( "4! = %d\n", fact(4) );
	return 0;
}
