//  求绝对值  
  
#include <stdio.h>  
#include <stdlib.h>

int my_abs(int a)
{  
    if (a < 0)  
    {  
        a =  ~a + 1;  
    }  
    return a;  
}  
  
int main()  
{  
    printf("绝对值是：%d\n", my_abs(5));  
    printf("绝对值是：%d\n", my_abs(0));  
    printf("绝对值是：%d\n", my_abs(-1));  
    return 0;  
}







