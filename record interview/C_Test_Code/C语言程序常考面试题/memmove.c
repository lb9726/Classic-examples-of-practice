#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <string.h>

void *my_memmove(void *dest, const void *source, size_t count)
{
    assert((NULL != dest) && (NULL != source));  // assert的作用是现计算表达式 expression ，如果其值为假（即为0），那么它先向stderr打印一条出错信息，然后通过调用 abort 来终止程序运行
    char *tmp_source, *tmp_dest;
    tmp_source = (char *)source;
    tmp_dest = (char *)dest;
//    if ((dest + count < source) || (source + count) < dest)
    if (dest <= source && ((dest + count) > source))
    {
        while(count--)
            *tmp_dest++ = *tmp_source++;
    }
    else
    { //如果有重叠（反向拷贝）
        tmp_source += count - 1;
        tmp_dest += count - 1;
        while(count--)
            *tmp_dest-- = *tmp_source--;
    }
    return dest;
}


int main()
{
    char str[10] = "abc";
    char st[10] = "abc";
    my_memmove(st + 1, st, strlen("abc"));
    printf("st = %s\n", st);
    memmove(str + 1, str, strlen("abc"));    
    printf("str = %s\n", str);
    
    
    my_memmove(st, st + 1, strlen("abc"));
    printf("st = %s\n", st);
    memmove(str, str + 1, strlen("abc"));    
    printf("str = %s\n", str);
    
}











