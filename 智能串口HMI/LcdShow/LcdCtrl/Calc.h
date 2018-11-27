#ifndef __LCD_CALC_H__
#define __LCD_CALC_H__

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 100

typedef char ElemType;
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
} sqStack;

typedef double dElemType;
typedef struct
{
    dElemType *base;
    dElemType *top;
    int stackSize;
} dsqStack;

double calc(char *buf);

#endif // __LCD_CALC_H__
