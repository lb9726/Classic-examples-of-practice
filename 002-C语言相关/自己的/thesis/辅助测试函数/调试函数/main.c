#include"debug.h" 
int main(int argc, char **argv) 
{
	char str[]="Hello World";
	DEBUG("A ha, check me: %s",str);
	DEBUG();
	return 0;
}
