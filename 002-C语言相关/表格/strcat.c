#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char p[100];
	strcpy(p,"nh");
	int j,n = 5;
	for(j = 0; j < n; j++)
	{
		strcat(p,"|");
	}
	sprintf(p,"%s|",p);
	printf("p = %s\n",p);
	return 0;
}
