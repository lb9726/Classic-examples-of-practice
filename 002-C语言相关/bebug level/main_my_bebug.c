#include "my_debug.h"
int main_section = 0;
int main_levels = 0;
int main(int argc, char **argv) 
{
	int i = 260, f = 249;	
	if (1 >= argc)
	{
		my_init_debug_levels(6, 251);
		my_debug(6, 252)("i = %d ; f = %d\n", i, f);
		printf("waring:: if you want input log, you can carry two argument!\n");
	}
	else
	{
		my_init_debug_levels(6, 251);
		my_debug(6, 250)("i = %d ; f = %d\n", i, f);
	}
	
	return 0;
}

void whetherPrintf(int counts, char **argm)
{
	
}
