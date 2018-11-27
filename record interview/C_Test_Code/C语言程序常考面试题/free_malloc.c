#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void Test()
{
    char *str = (char *)malloc(100);
    printf("malloc is str = %p\n", str);
    strcpy(str, "hello");
    free(str);
    printf("after free str = %p\n", str);
    if (NULL != str)
    {
        strcpy(str,"world");
        printf("str = %s after free\n", str);
    }
    printf("str = %c after free\n", *str);
    return ;
}

int main()
{
    Test();
    return 0;
}
