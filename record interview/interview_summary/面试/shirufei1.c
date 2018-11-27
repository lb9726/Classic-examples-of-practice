#include<stdio.h>
#include<stdlib.h>

int main()
{
    char *c[] = {"frist","second","third","last"};
    char **cp[] = {c+3, c+2, c+1, c};
    char ***cpp = cp;
    printf("***cpp = %p\n\n", cpp);
    printf("%s\n", **++cpp);
    printf("*c = %p\n", c);
    printf("*c+1= %p\n", c+1);
    printf("*c+2 = %p\n", c+2);
    printf("*c+3= %p\n", c+3);
    printf("**cp = %p\n", cp);
    printf("***cpp = %p\n", cpp);
    return 0;
}
