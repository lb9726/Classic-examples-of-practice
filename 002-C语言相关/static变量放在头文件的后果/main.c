
//main.c  
#include "a.h"  
#include <stdio.h>  
int main()
{  
    printf("a(%p) is %d\n",&a,a);  
    a = 2;  
    printf("a(%p) is %d\n",&a,a);  
    funcA();  
    printf("a(%p) is %d\n",&a,a);  
}
