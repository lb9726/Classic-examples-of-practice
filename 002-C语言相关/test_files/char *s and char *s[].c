#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
int main()
{
	char *s1 = "hello";
	char s2[] = "hello";
	char *a = "aaaaa";
	s1 = s2;
	//s2 = s1;
	s1[0] = 'a';
	strcpy(s1,"aaaaa");
	printf("%s\n",s1);
	strcpy(s1,a);
	printf("%s\n",s1);
	return 0;
}
