/*
读入一个整数K(2~10000),输出它的所有质因子(即所有为素数的因子).
例如:输入整数2310,则应输出2,3,5,7,11
*/

#include<stdio.h>

IsPrime(int n)
{
	int i, m;
	m = 1;
	for(i = 2; i < n; i++)
	{
		if( !(n%i) )  //如果n%i==0则说明是质数,将不会有因子,如果为1,则有因子
		{
			m = 0;
			break;
		}
	}
	return m;
}

int main()
{
	int j, k;
	printf("\nplease enter an interget number between 2 and 10000:");
	scanf("%d", &k);
	printf("\n\nThe prime factor(s) of %d is(are):", k);
	for(j = 2; j < k; j++)
		if((!(k%j)) && (IsPrime(j)))  //如果k%j==0 则j是k的因子,且j为质数时打印j
			printf("%4d", j);
	printf("\n");
	return 0;
}













