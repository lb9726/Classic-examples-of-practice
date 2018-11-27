#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <math.h>
#include <ctype.h>
#include "LcdCommon.h"
#include "Calc.h"

static char string[LCD_MSG_LENGTH];

void InitStack(sqStack *s)
{
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
}

void Push(sqStack *s , ElemType e)
{
    if (s->top - s->base >= s->stackSize) {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACK_INCREMENT) * sizeof(ElemType));
    }
    *(s->top) = e;
    s->top++;
}

void Pop(sqStack *s, ElemType *e)
{
    if (s->top == s->base) {
        return ;
    }
    *e = *(--(s->top));
}

int StackLen(sqStack *s)
{
    return (s->top - s->base);
}

void DestoryStack(sqStack *s)
{
    free(s->base);
    s->base = s->top = NULL;
    s->stackSize = 0;
}

void dInitStack(dsqStack *s)
{
    s->base = (dElemType *)malloc(STACK_INIT_SIZE * sizeof(dElemType));
    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
}

void dPush(dsqStack *s , dElemType e)
{
    if (s->top - s->base >= s->stackSize) {
        s->base = (dElemType *)realloc(s->base, (s->stackSize + STACK_INCREMENT) * sizeof(ElemType));
    }
    *(s->top) = e;
    s->top++;
}

void dPop(dsqStack *s, dElemType *e)
{
    if (s->top == s->base) {
        return ;
    }
    *e = *(--(s->top));
}

int dStackLen(sqStack *s)
{
    return (s->top - s->base);
}

void dDestoryStack(dsqStack *s)
{
    free(s->base);
    s->base = s->top = NULL;
    s->stackSize = 0;
}

void dealwith_youkuohao(sqStack *s, char e, int *li)
{
    Pop(s, &e);
    while ('(' != e)
    {
        printf("%c ",e);
        string[(*li)++] = e;
        string[(*li)++] = ' ';
        if (StackLen(s)) {
            Pop(s, &e);
        }
        else {
            break;
        }
    }
}

void dealwith_addorsub(sqStack *s, char c, char e, int *li)
{
    if (!StackLen(s)) {
        Push(s, c);
    }
    else {
        do
        {
            Pop(s, &e);
            if ('(' == e) {
                Push(s, e);
            }
            else {
                printf("%c ", e);
                string[(*li)++] = e;
                string[(*li)++] = ' ';
            }
        } while(StackLen(s) && '(' != e);

        Push(s, c);
    }
}

void dealwith_mult_or_divide(sqStack *s, char c, char e, int *li)
{
    if(StackLen(s))
    {
        Pop(s, &e);
        while('*' == e || '/' == e)
        {
            printf("%c ", e);
            string[(*li)++] = e;
            string[(*li)++] = ' ';
            if (StackLen(s)) {
                Pop(s, &e);
            }
            else {
                break;
            }
        }
        if ('(' == e || '+' == e || '-' == e) {
            Push(s, e);
        }
    }

    Push(s, c);
}

void Pop_all(sqStack *s, char e, int *li)
{
    while (StackLen(s))
    {
        Pop(s, &e);
        printf("%c ", e);
        string[(*li)++] = e;
        string[(*li)++] = ' ';
    }
}

void zhong_revert_hou(char *p)
{
    sqStack *s = NULL;
    int li;
    char c, e;

    li = 0;
    c = *p++;
    e = 0;
    s = (sqStack *)malloc(sizeof(sqStack));
    InitStack(s);

    while(c != '=')
    {
        while (c >= '0' && c <= '9')
        {
            printf("%c", c);
            string[li++] = c;
            c = *p++;
            if ((c < '0' || c > '9') && '.' != c) {
                printf(" ");
                string[li++] = ' ';
            }
            if ('.' == c) {
                printf("%c", c);
                string[li++] = c;
            }
        }

        if (')' == c) {
            dealwith_youkuohao(s, e, &li);
        }
        else if ('+' == c || '-' == c) {
            dealwith_addorsub(s, c, e, &li);
        }
        else if( '*' == c || '/' == c ) {
            dealwith_mult_or_divide(s, c, e, &li);
        }
        else if ('(' == c) {
            Push(s, c);
        }
        else if ('=' == c) {
            break;
        }
        else {
            // error
        }
        c = *p++;
    }

    Pop_all(s, e, &li);
    string[li] = '=';

    DestoryStack(s);
    free(s);
    s = NULL;

    return;
}

double calculate(/*char *p*/)
{
    int i, j;
    char c;
    double d = 0.0f, e = 0.0f;
    char str[LCD_MSG_LENGTH];
    dsqStack s;

    i = 0;
    j = 0;
    dInitStack(&s);
    c = string[j++];

    while (c != '=')
    {
        while(isdigit(c) || c == '.')
        {
            str[i++] = c;
            str[i] = '\0';
            if(i >= 10) {
                // error
                return -1;
            }
            c = string[j++];
            if(c == ' ') {
                d = atof(str);
                dPush(&s,d);
                i = 0;
                break;
            }
        }
        switch(c)
        {
        case '+':
            dPop(&s,&e);
            dPop(&s,&d);
            dPush(&s,d+e);
            break;
        case '-':
            dPop(&s,&e);
            dPop(&s,&d);
            dPush(&s,d-e);
            break;
        case '*':
            dPop(&s,&e);
            dPop(&s,&d);
            dPush(&s,d*e);
            break;
        case '/':
            dPop(&s,&e);
            dPop(&s,&d);
            if ( e != 0) {
                dPush(&s,d/e);
            }
            else
            {
                // error
                return -2;
            }
            break;
        }
        c = string[j++];
    }

    dPop(&s,&d);
    dDestoryStack(&s);

    printf("\nresult: %f\n",d);

    return d;
}


double calc(char *buf)
{
    zhong_revert_hou(buf);

    return calculate();
}
