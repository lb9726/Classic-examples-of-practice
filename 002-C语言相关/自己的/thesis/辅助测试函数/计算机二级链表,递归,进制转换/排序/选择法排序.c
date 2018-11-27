/*
选择法升序排序
*/

#include<stdio.h>
#define N 20
void fun(int a[],int n)
{
	int i,j,t,p;
	for(j=0;i<n-1;j++)
	{
		p=j;
		for(i=j+1;i<n;i++)
		{
			if(a[i]<a[p])
				p=i;
		}
		if(p!=j)
		{t=a[j];a[j]=a[p];a[p]=t;}//t=a[p];a[p]=a[j];a[j]=t;}
	}
}

void main()
{
	int a[N]={8,2,3,6,-1},i,m=5;
	printf("排序前数据:");
	for(i=0;i<m;i++)
	{
		printf("%3d",a[i]);
	}
	printf("\n");
	fun(a,m);
	printf("排序后的数据:");
	for(i=0;i<m;i++)
		printf("%3d",a[i]);	
	printf("\n");
}






