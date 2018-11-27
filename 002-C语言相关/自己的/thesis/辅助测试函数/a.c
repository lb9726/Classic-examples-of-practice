#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void array_sort_small_to_big(int a[],int n);
void print(int *a , int n);
//数组排序从小到大
void array_sort_small_to_big(int a[],int n)
{
	int i,j,temp;
	for(i = 0; i < n-1; i++ ) //外循环的趟数是数组个数减一
	{
		for(j = 0; j < n-i-1; j++)//每进行一次外循环内循环就减一
		{
			if(a[j] > a[j+1])//每一次外层循环内层循环都需要把相邻位置的两个数进行比较
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}print(a,n);
		}
	}
}

void print(int *a , int n)
{
	int i;
	for(i = 0; i < n ; i++)
	{
		printf("%-4d",a[i]);
	}
	printf("\n");
}

int main()
{	
	int n = 10;
	int a[n];
	srand(time(NULL));
	int i,j;
	for(i = 0; i < n ; i++)
		a[i] = rand()%100;
	printf("before sort:");
	print(a,n);
	array_sort_small_to_big(a,n);
	printf("after sort:");
	print(a,n);
	return 0;
	
}
