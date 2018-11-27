#include <stdio.h>
#include <stdlib.h>

int A;
int main()
{
    int power(int ); // 对调用的函数作声明
    int b = 3, c, d, m;
    printf("enter the number a and its power m: ");
    scanf("%d %d", &A, &m); // scanf其他字符需要原样输入，否则导致错误scanf("%d，%d", &A, &m); 要输入 3, 3才行
    c = A * b;
    printf("%d * %d = %d\n", A, b, c);
    d = power(m);
    printf("%d * %d = %d\n", A, m, d);
}
