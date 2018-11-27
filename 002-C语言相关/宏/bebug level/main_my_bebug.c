#include "my_debug.h"
int main(int argc, char **argv) 
{
	int i = 260,f = 249;
	my_init_debug_levels(3, 251);
	my_debug(MY_SECTION_nnnn, 250)("i = %d ; f = %d\n", i, f);
	return 0;
}
