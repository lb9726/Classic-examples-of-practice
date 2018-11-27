#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    char a;
    char *str = &a;
    strcpy(str,"hello");
    printf("str = %s\n", str);
    return 0;
}
