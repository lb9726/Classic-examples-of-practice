#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define N 20
void get_rand_str(char s[],int number)
{
	char str[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int i,t,j;
	char ss[6];
	srand(time(NULL));
	for(i=0;i<number;i++)
	{
		t=rand()%62;printf("%d",t);printf("\n");
		ss[i]=str[t];printf("i=%d\n",i);
		printf("%c",ss[i]);printf("\n");
	}
	puts(ss);printf("\n");
	ss[6]='\0';
	//for(j= 0;j<62;j++)
	//	printf("%c",str[j]);printf("\n");
}
/*
void autocreatnumber(int a[])//自动生成不同的数
{
    srand(time(NULL));
    int i=0,n=0,x;
    x=rand()%100+3;
    while(n<N-1)
    {
        for(i=0;i<n;i++)
            if(x==a[i])
                break;
       if(i==n)
       {
           a[n]=x;
           n++;
       } 
    x=rand()%100+3;
    }
}  
*/
int main()
{
	char s[6];
	int i,j;
	get_rand_str(s,5);
	//puts(s);
}
