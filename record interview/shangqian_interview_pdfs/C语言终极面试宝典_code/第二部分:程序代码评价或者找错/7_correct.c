#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *src = "hello,world";
    int len = strlen(src);
    char *dest = NULL;
    dest = (char *)malloc(len + 1); //要为\0 分配一个空间
    char *d = dest;
    char *s = &src[len - 1];        //指向最后一个字符
    while( len -- != 0)
    {
        *d++ = *s--;
    }
    *d = '\0';
    printf("%s\n", dest);
    free(dest);         // 使用完,应当释放空间,以免造成内存汇泄露
    return 0;
}

/*
运行结果：dlrow,olleh 
就是倒置一下
*/
