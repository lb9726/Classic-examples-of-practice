#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum TEST
{
    TEST0 = 0,
    TEST1 = 3,
    TEST2 = 4
};

enum T
{
    T0 = 0,
    T1,
    T2
};

typedef enum 
{
    N1 = 10,
    N2,
    N3,
    N4
}NAME;

NAME nameTest()
{
    return N1;
}

int main()
{
    int i  = 0;
    printf("TSET0 = %d\n", TEST0);
    printf("TSET1 = %d\n", TEST1);
    printf("TSET2 = %d\n", TEST2);
    printf("T0 = %d\n", T0);
    printf("T1 = %d\n", T1);
    printf("T2 = %d\n", T2);
    printf("nameTest() = %d\n", nameTest());
    return 0;
}
