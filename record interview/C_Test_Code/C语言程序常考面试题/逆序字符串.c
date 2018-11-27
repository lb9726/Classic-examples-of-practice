#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

void revert_string(char *str)
{
    int stringlen = strlen(str);
    char temp;
    int i = 0;
    int j = 0;
    //j = stringlen - 1 '\0' 不需要处理，所以需要减掉1
    //stringlen/2 当stringlen 为偶数时正中的两个数需要交换，为奇数则正中的数不需要处理
    for (i = 0, j = stringlen - 1; i < stringlen/2; i++,j--)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        printf(" stringlen = %d, i = %d , j = %d\n", stringlen, i , j);
    }
}

int main()
{
    char str[] = "abcdefg";
    revert_string(str);
    printf("str = %s\n", str);
    return 0;
}
