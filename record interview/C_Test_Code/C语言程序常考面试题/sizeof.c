#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 10

int main()
{
    int a[N];
    char str[6] = "hello";
    int length = sizeof(a);
    printf("length = %d\n", length);
    printf("sizeof(str) = %d\n", sizeof(str));
    printf("strlen(str) = %d\n", strlen(str));
    return 0;
}

/*
sizeof和是否初始化没有关系，就是分配了多少就是多少
strlen是以'\0'为结尾的字符串的检测
*/
