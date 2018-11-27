//============================================================================
// Name : debug.cpp
// Author : boyce
// Version : 1.0
// Copyright : pku
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#define __DEBUG__
#ifdef __DEBUG__
#define DEBUG(format,...) printf("File: "__FILE__", Line: %04d: "format"\n", __LINE__, ##__VA_ARGS__)
#else
#define DEBUG(format,...)
#endif

int main(int argc, char **argv) 
{
	char str[]="Hello World";
	DEBUG("A ha, check me: %s",str);
	DEBUG();
	return 0;
}
