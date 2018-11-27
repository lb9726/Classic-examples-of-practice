#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()  
{  
    int a[5] = {1, 2, 3, 4, 5};  
    int (*ptr)[5] = &a + 1;  
    //int* p = (int*)(&a + 1);  
    int* p = (int*)ptr;   
    printf("%d, %d \n", *(a + 1), *(p - 1));   
    printf("sizeof(a[5]) = %ld\n", sizeof(a));
    printf("sizeof(ptr) = %ld\n", sizeof(ptr));
    printf("sizeof(p) = %ld\n", sizeof(p));
    printf("(*ptr)[1] = %d\n", (*ptr)[1]);
    printf("(*ptr)[5] = %d\n", (*ptr)[5]);
    return 0;  
}
