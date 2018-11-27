//a.c  
#include <stdio.h>  
#include "a.h"  
funcA()
{  
    printf("in funcA():a(%p) is %d\n",&a,a);  
    a = 10;  
    printf("in funcA():after \"a = 10i\"a(%p) is %d\n",&a,a);  
} 
