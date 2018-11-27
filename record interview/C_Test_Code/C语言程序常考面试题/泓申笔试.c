// int *p[n] ； int (*)p[n]; int *p()；int (*)p()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 16

void get_array(int **p)
{
    int i,j;
    //int a[4][4]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    for (i = 0; i < N/4; i++)
    {
        for (i = 0; i < N/4; i++)
        {
            printf("%-3d",*(*(p+i)+j));
        }
        printf("\n");
    } 
}



int main()
{
    int a[4][4]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int *p[4];
    int (*)q[4];
    int (*m)(int **) = get_array;
//int (*)n(int **) = get_array;
    
    p[1] = a[1];
    q[2] = a[2];
    return 0;
}
// int* p(int x)；是一个返回值为int型指针的函数的声明










