/*
函数fun是将M航N列的二维数组中的数据,按列的顺序依次放到一位数组中.一维数组
中的数据的个数存放在形参n所指的存储单元中
*/

#include<stdio.h>
void fun(int (*s)[10],int *b,int *n,int mm,int nn)
{
	int i,j;
	for(j=0;j<nn;j++)
	{	
		for(i=0;i<mm;i++)
		{
			b[*n]=*(*(s+i)+j);//二维数组就相当于s[j][i]
			*n=*n+1;
		}
	}
}

int main()
{
	int w[10][10]={{33,33,33,33},{44,44,44,44},{55,55,55,55}},i,j;
	int a[100]={0},n=0;
	printf("\n");
	printf("The matrix:\n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
	    	printf("%3d",w[i][j]);
		printf("\n");
	}
	printf("\n");
	fun(w,a,&n,3,4);
	printf("The A array:\n");
	for(i=0;i<n;i++)
		printf("%3d",a[i]);
	printf("\n\n");
	return 0;
}
