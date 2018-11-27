/*
fun函数的功能是:删除一维数组中所有相同的数,使之只剩一个.数组中的数已经要先按照
从小到大的顺序排列,函数返回删除后数组中数据的个数
可以先排序然后，在删除即可
*/

#include<stdio.h>
#define N 80

int fun(int a[], int n)
{
	int i, j = 1;
	for(i = 1; i < n; i++)
	{
		if(a[j-1] != a[i])//若前一个和后一个数不相同就把后一个数存进数组中来
			a[j++] = a[i];
	}
	return j;
}

int main()
{
	int a[N] = {2, 2, 2, 3, 4, 4, 5, 6, 6, 6, 6, 7, 7, 8, 9, 9, 10, 10, 10, 10}, i, n = 20;
	printf("The original data:\n");
	for(i = 0; i < n; i++)
	{
		printf("%3d", a[i]);
	}
	n = fun(a, n);
	printf("\n\nThe data after deleted:\n");
	for(i = 0; i < n; i++)
		printf("%3d", a[i]);
	printf("\n\n");
	return 0;	
}
