/*
设有10个元素a[0]~a[9],将a[0]与a[1]~a[9]比较，若a[0]比a[1]~a[9]都小，则不进行交换，即无任何操作。若a[1]~a[9]中有一个以上比a[0]小，
则将其中最小的一个（假设为a[k])与a[0]交换，此时a[0]中存放了10个数中最小的数。
第二轮将a[1]与a[2]~a[9]比较，将剩下9个数中的最小者与a[1]交换，此时a[1]中存放的是10个数中次小的数。
以此类推，共进行9轮比较，a[0]到a[9]就已按由小到大的顺序存放了。
*/
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a[10];
	int i,j,k,t;
	printf("input 10 numbers :\n");
	for(i=0;i<10;i++)
		scanf("%d",&a[i]);
	printf("\n");
	for(i=0;i<9;i++)
	{
		k=i;
		for(j=i+1;j<=9;j++)
			if(a[k]>a[j]) k=j;  //该循环结束时，得到a[k]是a[i]~a[10]中最小值
		if(k!=i)                //若a[i+1]~a[10]中有一个比以上a[i]小，则
		{
			t=a[i];a[i]=a[k];a[k]=t; //将a[i+1]~a[10]中的最小者a[k]与a[i]交换
		}
	}
	printf("the sorted numbers :\n");
	for(i=0;i<10;i++)
		printf("%5d",a[i]);
	printf("\n");
	
}






