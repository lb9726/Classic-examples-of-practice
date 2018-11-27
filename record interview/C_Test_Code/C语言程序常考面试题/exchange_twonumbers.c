#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define swap_add(x,y) (x) = (x)+(y); (y) = (x)-(y); (x) = (x)-(y)
#define swap_yihuo(x, y) (x) = (x)^(y); (y) = (x)^(y); (x) = (x)^(y)

int main()
{
    int a = 2147483647;
    int b = 2100000000;
    int c = 2147483647;
    int d = 2100000000;
    printf("before exchange a = %d, b = %d\n",a, b);
    swap_add(a, b);
    printf("after exchange a = %d, b = %d\n",a, b);
    
    printf("before exchange a = %d, b = %d\n",c, d);
    swap_yihuo(c, d);
    printf("after exchange a = %d, b = %d\n",c, d);
    return 0;
}
