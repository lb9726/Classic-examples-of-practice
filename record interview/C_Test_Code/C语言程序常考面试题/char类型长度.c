#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char a[1000];
    int i;
    for(i=0; i<1000; i++)
    {
        a[i] = -1-i;
    }
    printf("i = %d\n", i);
    printf("%ld\n", strlen(a));
    return 0;
}
