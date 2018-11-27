#include<stdio.h>
#include<stdlib.h>
#include<string.h>

float get_abs(float a)
{
    float const expersion = 0.0000001;
    if (a < -expersion)
    {
        a = -a;
    }
    return a;
}

int main()
{
    float a;
    printf("请输入一个浮点类型的数:");
    scanf("%f", &a);
    printf("a的绝对值为%f\n", get_abs(a));
    return 0;
}
