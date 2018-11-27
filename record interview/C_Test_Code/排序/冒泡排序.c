#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define N 10

void autocreatenum(int a[])
{
	int i;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		a[i] = rand()%80;
}

void print(int a[])
{
	int i;
	for(i = 0; i < N; i++)
		printf("%4d",a[i]);
	printf("\n");
}

void buble(int a[])
{
    int i = 0,j;
    int temp;
    for (i = 0; i < N; i++)
    {
        for(j = 0; j < N-1; j++) // 冒泡排序是两两把相邻的两个数进行比较
        {
            if (a[j] < a[j+1])  // j < N - 1是指j+1 可能大于N会越界
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

int main()
{
    int a[N];
    autocreatenum(a);
    printf("排序之前:");
	print(a);
	printf("排序之后:");
	buble(a);
	print(a);
	return 0;
}








