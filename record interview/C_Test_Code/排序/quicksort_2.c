#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 10
#define SWAP(x,y) {int t; t = x; x = y; y = t;}

void quicksort(int [], int ,int);
void autocreatenum(int a[]);
void print(int a[]);

void quicksort(int number[], int left, int right)
{
	int i, j, s;
	if (left < right)
	{
		s = number[(left + right)/2];
		i = left - 1;
		j = right + 1;
		
		while (1)
		{
			//向右找，当找到一个大于s的数时退出循环，后面向左找
			while (number[++i] < s); 
			// 向左找，当找到一个小于s的数时退出循环，后面判断i，j 是否需要交换
			while (number[--j] > s);
			if (i >= j)
				break;
			SWAP(number[i], number[j]);
		}
		
//		number[left] = number[j];
//		number[j] = s;
		
		quicksort(number, left, i-1);   // 对左边进行递归
		quicksort(number, j+1, right);  // 对右边进行递归
	}
}

void autocreatenum(int a[])
{
	int i;
	srand(time(NULL));
	for(i = 0; i < MAX; i++)
		a[i] = rand()%80;
}

void print(int a[])
{
	int i;
	for(i = 0; i < MAX; i++)
		printf("%4d", a[i]);
	printf("\n");
}

int main(void)
{
	int number[MAX] = {0};
	autocreatenum(number);
	printf("排序前:");
	print(number);
	printf("排序后:");
	quicksort(number, 0, MAX-1);
	print(number);
	return 0;
}













