//
//  main.c
//  BigNumAdd
//
//  Created by 小甲鱼 on 13-1-4.
//  Copyright (c) 2013年 小甲鱼. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT  10

typedef char ElemType;
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;


// 函数功能：初始化栈
// 参数*s：栈的地址
void InitStack(sqStack *s)
{
    // 内存中开辟一段连续空间作为栈空间，首地址赋值给 s->base，请鱼油务必要掌握！
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if( !s->base )
    {
        exit(0);
    }

    s->top = s->base;                   // 最开始栈顶指向栈底
    s->stackSize = STACK_INIT_SIZE;
}

// 函数功能：入栈操作
// 参数e：即将压入栈的变量
void Push(sqStack *s, ElemType e)
{
    // 如果栈满，追加空间，鱼油务必掌握！
    if( s->top - s->base >= s->stackSize )
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !s->base )
        {
            exit(0);
        }

        s->top = s->base + s->stackSize;
        s->stackSize = s->stackSize + STACKINCREMENT;
    }

    *(s->top) = e;      // 数据e入栈
    s->top++;           // 修改栈顶指针
}

// 函数功能：出栈操作
// 参数*s：栈的地址
// 参数*e：存放从栈中弹出的变量
void Pop(sqStack *s, ElemType *e)
{
    // 如果栈顶指针指向栈底，说明栈已空
    if( s->top == s->base )
    {
        return;
    }
    *e = *--(s->top);   // 弹出变量并修改栈顶指针
}

// 函数功能：计算栈s当前的长度
int StackLen(sqStack *s)
{
    return (s->top - s->base);
}

void ADD(sqStack *s1, sqStack *s2, sqStack *s3)
{
    char a, b, c, carry = 0;

    while( StackLen(s1) !=0 && StackLen(s2) !=0 )
    {
        Pop(s1, &a);
        Pop(s2, &b);

        c = (a-48) + (b-48) + carry + 48;   // －48得到实际数相加后再＋48得到该数的ascii码值

        if( c > '9' )
        {
            c = c - '9' + 47;           // 聪明的鱼油猜猜看，为什么是47而不是48？
            carry = 1;                  // 产生进位
        }
        else
        {
            carry = 0;                  // 不产生进位
        }

        Push(s3, c);
    }

    if(StackLen(s1) != 0)
    {
        while(StackLen(s1) != 0)
        {
            Pop(s1, &a);
            c = a + carry;

            if( c > '9' )
            {
                c = c - '9' + 47;
                carry = 1;
            }
            else
            {
                carry = 0;
            }

            Push(s3, c);
        }
    }
    else if(StackLen(s2) != 0)
    {
        while(StackLen(s2) != 0)
        {
            Pop(s2, &b);
            c = b + carry;

            if( c > '9' )
            {
                c = c - '9' + 47;
                carry = 1;
            }
            else
            {
                carry = 0;
            }

            Push(s3, c);
        }
    }

    // 如果最后有进位，将字符1压入栈s3中
    if( carry == 1 )
    {
        Push(s3, '1');
    }
}

int main()
{
    char e;
    sqStack s1, s2, s3;

    InitStack(&s1);
    InitStack(&s2);
    InitStack(&s3);

    printf("请输入第一串任意整数，输入＃表示结束：");
    scanf("%c", &e);
    while( e != '#' )
    {
        Push(&s1, e);
        scanf("%c", &e);
    }
    getchar();      // 回收回车符

    printf("\n请输入第二串任意整数，输入＃表示结束：");
    scanf("%c", &e);
    while( e != '#' )
    {
        Push(&s2, e);
        scanf("%c", &e);
    }
    getchar();      // 回收回车符

    ADD(&s1, &s2, &s3);

    printf("\n两者的和是：");
    while(StackLen(&s3) != 0)
    {
        Pop(&s3, &e);
        printf("%c", e);
    }

    return 0;
}

