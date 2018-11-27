//#ifndef TEST_H
//#define TEST_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
int libo = 1;
/tmp/ccVL7psK.o:(.data+0x0): multiple definition of `libo'
/tmp/ccIBLD1S.o:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status
*/
int libo; // 不会出现重定义
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

NAME nameTest();

//#endif
