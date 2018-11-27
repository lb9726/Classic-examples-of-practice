#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

void print(char *str)
{   
    if (*str == '\0')
        return ;
    print(str+1);
    printf("%c", *str);
}

int main()
{
    char str[] = "abcdefg";
    print(str);
    printf("\n");
    return 0;
}
