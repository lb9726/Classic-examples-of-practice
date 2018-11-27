#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main()
{
	int i,j;
	int n;//这个就是需要指定的行数
	char (*p)[8];
	scanf("%d",&n);//取得行数
	
	/*
	//动态生成二维数组,指定列数为10，如果想改,自己该里面 
的参数,如果想定义n行2列就为: p=(int (*)[2])malloc(n*2*sizeof(int)); 
	*/
	p=(char (*)[8])malloc(n*8*sizeof(char)); 
	for(i = 0;i < n; i++)
		for(j = 0;j < 8;j++)
		strcpy(p[i][j],"lihua");
	for(i = 0;i < n; i++)
		for(j = 0;j < 8;j++)
			printf("%s",p[i][j]);	
	printf("\n");
	free(p);
	return 0;
}

