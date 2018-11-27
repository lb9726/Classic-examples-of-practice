/*
求三个数的最小公倍数,x1,x2,x3 分别输入15,11,2,则输出结果为330
*/

#include<stdio.h>
int fun(int x, int y, int z)  //不写默认int的
{
	int j, t, n, m;
	j = 1;
	t = j%x;
	m = j%y;
	n = j%z;
	
	while(t != 0 || m != 0 || n != 0)
	{
		j = j + 1;
		t = j%x;
		m = j%y;
		n = j%z;
	}
	return j;
}

int main()
{
	int x1, x2, x3, j;
	printf("Input x1 x2 x3:");
	scanf("%d%d%d", &x1, &x2, &x3);
	printf("x1 = %d, x2 = %d, x3 = %d\n",x1,x2,x3);
	j=fun(x1, x2, x3);
	printf("The minimal common multiple is:%d\n", j);
}






