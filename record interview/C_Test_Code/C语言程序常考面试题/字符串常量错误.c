#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char *s = "AAA";
    printf("%s\n", s);
    s[0] = 'B';
    printf("%s\n", s);
    return 0;
}
