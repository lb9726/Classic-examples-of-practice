//已知原始数组: int a[6]={1,2,3,4,5,6}; 要求所有元素值变成: 0 1 2 3 4 5 (相当于右移1格，右边第一个数被挤掉，左边空格补0)
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define N 20
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

void print(int a[],int n)
{
    int i=0;
    for(i=0;i<n-1;i++)
       printf("%4d",a[i]);
	printf("\n");
} 

void xunhuanyouyi(int a[])
{
	int i=0;
	for(i=N-1;i>=1;i--)
	{
		a[i]=a[i-1];
	}
	a[0]=0;
}

int main()
{
	int a[N];
	printf("自动生成的数据如下:\n");
	autocreatnumber(a);
	print(a,N);
	printf("循环右移之后的数据如下:\n");
	xunhuanyouyi(a);
	print(a,N);
	return 0;
}
