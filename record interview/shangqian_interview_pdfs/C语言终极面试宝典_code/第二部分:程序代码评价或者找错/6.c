#include <stdio.h>
#include <stdlib.h>

int inc(int a)
{
    return (++a);
}

int multi(int *a, int *b, int *c)
{
    return (*c = *a * *b);
}

typedef int(FUNC1) (int in);
typedef int(FUNC2) (int *, int *, int *);

// 函数指针用来作函数参数
void show(FUNC2 fun, int arg1, int *arg2)
{
//    inc *p = &inc; //6.c:19:5: error: ‘INCp’ undeclared (first use in this function)
//  int temp = p(arg1);
    int (*p)(int) = inc;
    int temp = p(arg1);
    fun(&temp, &arg1, arg2);
    printf("%d\n", *arg2);
}

int main()
{
    int a;
    show(multi, 10, &a);
    return 0;
}


/*
运行结果：110
*/
