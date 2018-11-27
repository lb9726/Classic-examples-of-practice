/*
设有10个元素a[0]~a[9],将a[0]与a[1]~a[9]比较，若a[0]比a[1]~a[9]都小，则不进行交换，即无任何操作。若a[1]~a[9]中有一个以上比a[0]小，
则将其中最小的一个（假设为a[k])与a[0]交换，此时a[0]中存放了10个数中最小的数。
第二轮将a[1]与a[2]~a[9]比较，将剩下9个数中的最小者与a[1]交换，此时a[1]中存放的是10个数中次小的数。
以此类推，共进行9轮比较，a[0]到a[9]就已按由小到大的顺序存放了。
*/

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

void select_sort(int a[])
{
    int i, j, temp, p;
    for(i = 0; i < N; i++)
    {
        for(j = i + 1; j < N; j++)
        {
            if (a[i] < a[j])  // 选择法排序，是指一轮之后必定将最小的放在第一位或将最大的放在第一位
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
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
	select_sort(a);
	print(a);
	return 0;
}






