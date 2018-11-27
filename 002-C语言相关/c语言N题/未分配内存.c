#include<stdio.h>
#include<string.h>

int main()
{
	char a;
	char *str = &a;
	//strcpy(str,"hello");
	strcpy(str,"");
	printf("%s\n",str);
	return 0;
}
