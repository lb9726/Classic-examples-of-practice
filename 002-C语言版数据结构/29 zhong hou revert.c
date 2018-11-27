#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include<ctype.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define MAXBUFFER 10

typedef char ElemType;
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack;

void InitStack(sqStack *s)
{
	s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (!s->base)   //如果分配失败退出程序
	{
		exit(0);
	}
	s->top = s->base;  //栈的初始化时栈顶和栈底指向同一个地址
	s->stackSize = STACK_INIT_SIZE;
}

void Push(sqStack *s, ElemType e)
{
    //如果栈已经满了则再追加空间
	if (s->top - s->base >= s->stackSize)
	{
		 s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) *sizeof(ElemType));
		 if(!s->base) //如果分配失败退出程序
		 	exit(0);	 
	}
	*(s->top) = e;
	s->top++;
}

void Pop(sqStack *s, ElemType *e)
{
	if (s->top == s->base)
	{
		return ;
	}
	*e = *--(s->top); // 出栈时会将当前的栈顶的元素给e
}


// 有的时候用指针，有的时候用不用指针，一般对内容修改的用指针，其余的不用指针
int StackLen(sqStack s)
{
	return (s.top - s.base);
}

int main()
{
	sqStack s;
	char c,e;
	InitStack(&s);
	printf("请输入中缀表达式， 以#作为结束标志：\n");
	scanf("%c",&c);
	while (c != '#')
	{
		while (c >= '0' && c <= '9')
		{
			printf("%c",c);
			scanf("%c",&c);
			if (c < '0' || c > '9') // 不是数字才打印空格，使得中缀表达式数字之间有该有的空格
			{
				printf(" ");
			}
		}
		if ( ')' == c)             // 如果输入为右括号，则表明栈中必定会有左括号
		{
			Pop(&s,&e);            // 栈中元素和左括号比较则出栈，直到遇到左括号
			while ('(' != e)       //比较栈顶元素是不是左括号
			{
				printf("%c ",e);   // 出栈时打印数据
				Pop(&s,&e);
			}
			
		}
		else if ( '+' == c || '-' == c)
		{
			if ( !StackLen(s))
			{
				Push(&s,c);// 如果为空，则将输入的符号入栈
			}
			else           // 不为空时，先出栈
			{
				do 
				{
					Pop(&s,&e);  // 通过pop得到当前栈顶元素的值
					if ('(' == e)
					{
						Push(&s,e);
					}
					else        // 可能为+ - * / 这几种可能
					{
						printf("%c ",e);  //将栈内数据打印出来
					}
				}while(StackLen(s) && '(' != e);// 如果不为空并且不是左括号则继续出栈
				Push(&s,c);
			}
		}
		else if ('*' == c || '/' == c || '(' == c)
		{
			Push(&s,c);
		}
		else if ('#' == c)
		{
			break;
		}
		else 
		{
			printf("\n 出错，用户输入错误!\n");
		}
	scanf("%c",&c);
	}
	while ( StackLen(s))
	{
		Pop(&s,&e);
		printf("%c ",e);
	}
	printf("\n");
	//printf("\n 最终的计算结果为：%f\n",d);
	return 0;
}












