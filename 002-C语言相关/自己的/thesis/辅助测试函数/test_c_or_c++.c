#ifdef __cplusplus    /*判断是否用C++编译器?*/  
#define USING_C 1    /*是用C编译器*/  
#else  
#define USING_C 0    /*是用C++编译器*/  
#endif  
#include <stdio.h>  
  
int main()  
{  
    if(USING_C)   
        printf("C++\n");  
    else   
        printf("C\n");  
    return 0;  
}  
