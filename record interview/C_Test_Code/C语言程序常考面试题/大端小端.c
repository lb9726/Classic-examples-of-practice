#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    int a = 0x12345678;
    char *p;
    p = (char *)(&a);  //&取地址取到的是栈底的地址
    printf("&a = %p\n", &a); 
    
    if (0x78 == (*p))
    {
        printf("小端\n");
    }
    else
    {
        printf("大端\n");
    }
    p++;
    printf("*p = %X\n",*p);
    printf("p = %p\n", p);
    p++;
    printf("*p = %X\n",*p);
    printf("p = %p\n", p);
    p++;
    printf("*p = %X\n",*p);
    printf("p = %p\n", p);
    return 0;
}



