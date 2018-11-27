
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int gcd(int a, int b);//求两个数的最大公约数
int max_common_divisor(int several[], int n);//求n个数的最大公约数


int gcd(int n, int m)
{
    if (n < m)
    {
        n = m + n;
        m = n - m;
        n = n - m;
    }
    if (m == 0) return n;
    return gcd(m, n%m);
}

int max_common_divisor(int several[], int n)
{
    int a = several[0];
    int b = several[1];
    int c = gcd(a, b);
    int i;
    for (i = 2; i < n; i++)
    {
        c = gcd(c, several[i]);
    }
    return c;
}

int main()
{
    int a[4];
    int x, y;
    a[0] = 147;
    a[1] = 210;
    a[2] = 315;
    a[3] = 84;
    printf("最大公约数为：%d\n",max_common_divisor(a, 4));
    return 0;
}

















