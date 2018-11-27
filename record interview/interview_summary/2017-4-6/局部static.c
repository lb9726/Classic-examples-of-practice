#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void increasing()
{   
    static int i = 0;
    i = i + 1;
    printf("i = %d\n", i);
    return;
}

void increasing2()
{   
    int j = 0;
    j = j + 1;
    printf("j = %d\n", j);
    return;
}

int main()
{
    increasing();
    increasing();
    increasing2();
    increasing2();
    return 0;
}
