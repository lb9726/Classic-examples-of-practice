#include<stdio.h>
#include<stdlib.h>

#define MIN(x,y) ((x)>(y)?(y):(x))

int main()
{
    int a = 11, b = 12;
    printf("min = %d\n", MIN(a, b));
    return 0;
}
