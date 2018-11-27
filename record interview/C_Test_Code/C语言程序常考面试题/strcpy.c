#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>

char *my_strcpy(char *dst,const char *src)  
{  
    assert(dst != NULL);  
    assert(src != NULL);  
    char *ret = dst;  
    while((* dst++ = * src++) != '\0')   
        ;  
    return ret;  
}

int main()
{
    char str[10] = "abc";
    char st[10] = "abc";
    strcpy(st + 1, st);
    printf("st = %s\n", st);
    my_strcpy(str + 1, str);    
    printf("str = %s\n", str);
    
}
