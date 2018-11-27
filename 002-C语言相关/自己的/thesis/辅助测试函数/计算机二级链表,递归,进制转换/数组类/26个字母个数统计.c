#include <stdio.h>
#include<string.h>
void fun(char *tt ,int pp[])
{
   int i;
   for(i=0;i<26;i++)
       pp[i]=0;
   while(*tt)
  	   if(*tt<='z'&&*tt>='a')
   	   { 
   	       pp[*tt-'a']++; 
   	       tt++;
   	   }
}

int main()
{
  char aa[100];
	int bb[26],m;
	printf("ÇëÊäÈëÒ»¸ö×Ö·û´®\n");
	scanf("%s",aa);
	int k=0;
	for(;1;)
	{ 
		if(aa[k]!='\0')
	    	k++;
   		else 
	   		break;
	}
	printf("k=%d\n");
	fun(aa,bb);
	for(m=0;m<26;m++)
   		printf("%d",bb[m]);
	printf("\n");
	return 0;
}
