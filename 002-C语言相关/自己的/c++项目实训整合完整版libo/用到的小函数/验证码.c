#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define N 20
char checknum[6];
void get_rand_str(char s[],int number)
{
	char str[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int i,t,j;
	char ss[6];
	srand(time(NULL));
	for(i=0;i<number;i++)
	{
		t=rand()%62;
		ss[i]=str[t];
	}
	puts(ss);printf("\n");
	ss[6]='\0';
    strcpy(checknum,ss);
    
}

int main()
{
	char s[6];
	int i,j;
	get_rand_str(s,5);
	//puts(s);
	puts(checknum);printf("\n");
}
