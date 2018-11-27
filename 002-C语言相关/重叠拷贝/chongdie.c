#include<stdio.h>
#include<stdlib.h>

int main()
{
    char *p = NULL;
    p=(char*)malloc(100);
    printf("sizeof(123456789) = %d\n",strlen("123456789"));
    memcpy(p,"123456789",strlen("123456789")); //会等到错误的结果，有一个长度参数，只能拷贝cnt个
    //字节就结束了
    printf("before p = %s\n",p);
    strcpy(p+1,p); //注意：这里重叠了，而strcpy是根据判断原串中的'\0'
    printf("after p = %s\n",p);
    free(p);
}
