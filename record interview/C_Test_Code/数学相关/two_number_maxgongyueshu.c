/*
求两个数的最大公约数的方法

(1)辗转相除法
有两整数a和b：
若a>b为真，进行如下操作，否则交换a，b的值
① a%b得余数c
② 若c=0，则b即为两数的最大公约数
③ 若c≠0，则a=b，b=c，再回去执行①

要考虑用户输入的是否有0,是否包含负数等情况进行处理
如果为0，则提示0和任何数都没有最大公约数
其中一个为负数时，则将负数取绝对值，因为求最大的，所以肯定为正数
如果均为负数，都求绝对值来计算，方法都可以使用辗转相除法

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int judge_input(int a, int b)
{
    int flag = 0; //printf("a = %d, b = %d\n", a, b);
    if (0 == a || 0 == b)
    {
        flag = 1; //printf("flag = %d\n", flag);
        return flag;
    }
    return flag;
}

int Max_gongyueshu_twonumber(int a, int b)
{
    int temp;
    int Max;
    a = abs(a);
    b = abs(b);
    if (a < b)
    {
        temp = a;
        a = b;
        b = temp;
    }
    int remain;
    while(0 != b)
    {
        remain = a % b;
        a = b;
        b = remain;
    }
    Max = a;  //当remain余数为0的时候，说明赋值给a的b为最大公约数
    return Max;    
}

int main()
{
    int a, b, max;
    int flag;
    printf("请输入两个数，a和b:");
    scanf("%d%d", &a, &b);
    flag = judge_input(a, b); //printf("a = %d , b = %d ,flag = %d\n", a, b, flag);
    while (flag)
    {
        printf("0和任何数都没有最大公约数, 请重新输入两个数\n");
        scanf("%d%d", &a, &b);
        flag = judge_input(a, b);
    }
    max = Max_gongyueshu_twonumber(a, b);
    printf("%d 和 %d的最大公约数为 %d\n", a, b, max);
    return 0;
}



























