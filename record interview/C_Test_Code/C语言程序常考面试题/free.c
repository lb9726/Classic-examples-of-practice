#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void getmemory(char *p)
{
    p = (char *)malloc(100);
    memset(p, 0, 100);
    printf("will copy string to p = %p\n",p);
    strcpy(p, "hello world");
    printf("will copy string to p = %p\n",p);
    printf("p = %s\n", p);
}

int main()
{
    char *str = NULL;
    getmemory(str);
    printf("main function is gone\n");
    //strcpy(str, "hello world");
    printf("%s\n", str);
    printf("printf is gone\n");
    free(str);
    return 0;
}
