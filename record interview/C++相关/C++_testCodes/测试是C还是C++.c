#include<stdio.h>

#ifdef __cplusplus
#define USING_C 0
#else
#define USING_C 1
#endif

int main()
{
      if(USING_C)
            printf("C\n");
      else 
            printf("C++\n");
      return 0;
}
