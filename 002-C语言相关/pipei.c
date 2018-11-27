#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT  10

typedef char ElemType;
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;

InitStack(sqStack *s)
{
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if( !s->base )
        exit(0);

    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
}

Push(sqStack *s, ElemType e)
{
    // 栈满，追加空间，鱼油必须懂！
    if( s->top - s->base >= s->stackSize )
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !s->base )
            exit(0);

        s->top = s->base + s->stackSize;
        s->stackSize = s->stackSize + STACKINCREMENT;
    }

    *(s->top) = e;      // 存放数据
    s->top++;
}

Pop(sqStack *s, ElemType *e)
{
    if( s->top == s->base )
        return;

    *e = *--(s->top);   // 将栈顶元素弹出并修改栈顶指针
}

int StackLen(sqStack s)
{
    return (s.top - s.base);
}

int match(char e, char c)
{
    if( e=='(' && c==')' )
        return 1;
    if( e=='[' && c==']' )
        return 1;
    if( e=='<' && c=='>' )
        return 1;
    if( e=='{' && c=='}' )
        return 1;
    if( e=='\' && c=='\' )
        return 1;
    if( e=='\' && c=='\' )
        return 1;

    return 0;
}

int main()
{
    sqStack s;
    char c, e;

    InitStack( &s );

    printf("请输入一系列字符串，以#作为结束标志：");
    scanf("%c", &c);
    while( c != '#' )
    {
        // 如果是括号，就压栈
        if( c=='(' || c==')' || c=='[' || c==']' || c=='<' || c=='>' || c=='\' || c=='\' || c=='{' || c=='}' )
        {
            if( !StackLen(s) )
            {
                Push(&s, c);
            }
            else
            {
                Pop(&s, &e);
                if( !match(e, c) )
                {
                    Push(&s, e);
                    Push(&s, c);
                }
            }
        }

        scanf("%c", &c);    // 输入下一个字符
    }

    if( !StackLen(s) )
    {
        printf("\n输入字符串中的括号完全匹配！\n");
    }
    else
    {
        printf("\n输入字符串中的括号不完全匹配！\n");
    }

    return 0;
}

