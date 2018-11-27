#include <stdio.h>
#include <stdlib.h>

int max(int x, int y)
{
    int z;
    z = x > y ? x : y;
    return (z);
}

int main()
{
    extern /*int*/ A, B;
    printf("max = %d\n", max(A, B));
}

int A = 13, B = -8;
