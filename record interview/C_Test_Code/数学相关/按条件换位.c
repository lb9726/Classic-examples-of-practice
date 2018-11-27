/*
fun函数的功能:计算形参x所指数组中N个数的平均值(规定所有数均为整数),将所指
数组中大于平均值的数据移至数组的前部,小于等于平均值的数据移至x所指数组的后部,平均值
作为函数值返回,在主函数中输出平均值和移动后的数据
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 10

double fun(double *x)
{
	int i,j;
	double s,av,y[N];
	s = 0;
	for(i = j = 0; i < N; i++)
		s = s+x[i];
	av = s/N;
	for(i = j =0; i < N; i++)
	{
	    if(x[i] > av)
		{
		 	y[j++] = x[i];
			x[i] = -1;
		}
	}
	for(i = 0; i < N; i++)
	{
		if(x[i] != -1)
			y[j++] = x[i];
	}
	for(i = 0; i < N; i++)
		x[i] = y[i];
	return av;
}

int main()
{
	int i;
	srand(time(NULL));
	double x[N];
	for(i = 0; i < N; i++)
	{
		x[i] = rand()%50;
		printf("%4.0f", x[i]);
	}
	printf("\n");
	printf("\nThe average is :%f\n", fun(x));
	printf("\nThe result :\n");
	for(i = 0; i < N; i++)
		printf("%5.0f", x[i]);
	printf("\n");
	return 0;
}


















