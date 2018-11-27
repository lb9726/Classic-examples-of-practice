#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *GetMemory()
{
    char p[] = "hello world";
    //printf("p = %s\n", p);
    //printf("p = %p\n",p);
    return p;
}

int main()
{
    char *str = NULL;
    str = GetMemory();
    printf("str = %s\n", str);
    return 0;
}
