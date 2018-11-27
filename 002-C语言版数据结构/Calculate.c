#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define MAXBUFFER 10

char string[100];

typedef char ElemType;
typedef struct 
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;

typedef double dElemType;
typedef struct 
{
    dElemType *base;
    dElemType *top;
    int stackSize;
}dsqStack;

void InitStack(sqStack *s)
{
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (!s->base)
    {
        exit(0);  //如果分配失败退出程序
    }
    s->top = s->base;    //栈的初始化时栈顶和栈底指向同一个地址
    s->stackSize = STACK_INIT_SIZE;
}

void Push(sqStack *s , ElemType e)
{
    //如果栈已经满了则再追加空间
    if (s->top - s->base >= s->stackSize)
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT)*sizeof(ElemType));
        if (!s->base)
        {
            exit(0);
        }
    }
    *(s->top) = e;  // 给当前的栈顶赋值
    s->top++;     // 然后栈顶指针加一
}

void Pop(sqStack *s, ElemType *e)
{
    if (s->top == s->base)
    {
        return ;
    }
    *e = *(--(s->top));  // 出栈时栈顶指针先减一再取当前的栈顶的元素给e
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
    if (!s->base)
    {
        exit(0);  //如果分配失败退出程序
    }
    s->top = s->base;    //栈的初始化时栈顶和栈底指向同一个地址
    s->stackSize = STACK_INIT_SIZE;
}

void dPush(dsqStack *s , dElemType e)
{
    //如果栈已经满了则再追加空间
    if (s->top - s->base >= s->stackSize)
    {
        s->base = (dElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT)*sizeof(ElemType));
        if (!s->base)
        {
            exit(0);
        }
    }
    *(s->top) = e;  // 给当前的栈顶赋值
    s->top++;     // 然后栈顶指针加一
}

void dPop(dsqStack *s, dElemType *e)
{
    if (s->top == s->base)
    {
        return ;
    }
    *e = *(--(s->top));  // 出栈时栈顶指针先减一再取当前的栈顶的元素给e
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

// deal with number
int dealwith_digital(char c, int *li, char *p)
{
    int i = 0;
    while (c >= '0' && c <= '9') // 处理连续数字
    {
        printf("%c",c);
        string[(*li)++] = c;
        //scanf("%c",&c);
        c = *p++;
        i++;
        if ((c < '0' || c > '9') && '.' != c) // 不是数字才打印空格，使得中缀表达式数字之间有该有的空格,因为数字可以是多位数的
        {
            printf(" "); 
            string[(*li)++] = ' ';
        }
        if ('.' == c)
        {
            printf("%c",c);
            string[(*li)++] = c;
        }
    }
    //printf("i = %d\n", i);
    return i;
}

// deal with ')'
void dealwith_youkuohao(sqStack *s, char e, int *li)
{
    Pop(s,&e);            // 栈中元素和左括号比较则出栈，直到遇到左括号
    while ('(' != e)      //比较栈顶元素是不是左括号
    {
        printf("%c ",e);   // 出栈时打印数据
        string[(*li)++] = e;
        string[(*li)++] = ' ';
        if (StackLen(s))
        {
            Pop(s,&e);
         }
         else
         {
            break;
         }           
    }           
}

// deal with + -
void dealwith_addorsub(sqStack *s, char c, char e, int *li)
{
    if ( !StackLen(s))
    {
        Push(s,c);// 如果栈为空，则将输入的符号入栈
    }
    else           // 不为空时，先出栈
    {
        do 
        {
            Pop(s,&e);  // 通过pop得到当前栈顶元素的值
            if ('(' == e)
            {
                Push(s,e);// 如果左括号再重新压栈
            }
            else        // 可能为+ - * / 这几种可能
            {
                printf("%c ",e);  //否则将栈内数据打印出来
                string[(*li)++] = e;
                string[(*li)++] = ' ';
             }
        }while(StackLen(s) && '(' != e);// 如果不为空并且不是左括号则继续出栈
        Push(s,c);
    }
}

//deal with * /
void dealwith_mult_or_divide(sqStack *s, char c, char e, int *li)
{
    if(StackLen(s))
    {
        Pop(s,&e);
        while('*' == e || '/' == e)  //当栈顶元素为* / 时则弹栈顶元素
        {
            printf("%c ",e);
            string[(*li)++] = e;
            string[(*li)++] = ' ';
            if (StackLen(s))
            {
                Pop(s,&e);
            }
            else
            {
                break;
            }
        }
        if ('(' == e || '+' == e || '-' == e)   // 当pop后刚好为（，+ - 均需要压栈
        {
            Push(s,e);
        }
    }
    Push(s,c);
}

// Pop all
void Pop_all(sqStack *s, char e, int *li)
{
    while ( StackLen(s))
    {
        Pop(s,&e);
        printf("%c ",e);
        string[(*li)++] = e;
        string[(*li)++] = ' ';
    }
}
// 将中缀表达式（即标准形式的表达式）转换为后缀表达式
void zhong_revert_hou(char *p)
{
    sqStack *s = NULL;
    s = (sqStack *)malloc(sizeof(sqStack));
    char c, e ;
    InitStack(s);
    int li = 0;
    c = *p++;
    while( c != '=')
    {
        dealwith_digital(c, &li, p);
        if (')' == c)
        {
            dealwith_youkuohao(s, e, &li);
        }
        else if ('+' == c || '-' == c)
        {
            dealwith_addorsub(s, c, e, &li);
        }
        else if( '*' == c || '/' == c )
        {
            dealwith_mult_or_divide(s, c, e, &li);
        }
        else if ('(' == c)
        {
            Push(s, c);
        }
        else if ('=' == c)
        {
            break;
        }
        else 
        {
            if ( '.' != c && ('0' > c || '9' < c))
                printf("\n 出错，用户输入错误!\n");
        }
        c = *p++;
    }
    Pop_all(s, e, &li);
    printf("\n");
    string[li] = '\0';
    printf("%s \n", string);
    string[li] = '=';
    DestoryStack(s);
    free(s);
    s = NULL;
    return;
}

void calculate()
{
    dsqStack s;
	char c;
	double d,e;
	char str[MAXBUFFER];
	int i = 0;
	dInitStack(&s);
	printf("请按逆波兰表达式输入待计算数据，数据与运算符之间用空格隔开， 以 = 作为结束标志：\n");
	char *p = string;
	c = *p++;
	//scanf("%c",&c);
	while (c != '=')
	{
		while(isdigit(c) || c == '.')
		{
			str[i++] = c;
			str[i] = '\0';
			if( i >= 10)
			{
				printf("error:输入的单个数据过大！\n");
				return ;
			}
			//scanf("%c",&c);
			c = *p++;
			if( c == ' ')
			{
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
				if ( e != 0)
				{
					dPush(&s,d/e);
				}
				else
				{
					printf("\nerror:除数不能为零！\n");
					return ;
				}
				break;
		}
		//scanf("%c",&c);
		c = *p++;
	}
	dPop(&s,&d);
	printf("\n 最终的计算结果为：%f\n",d);
	dDestoryStack(&s);
	return ;
}

int main()
{
    char s[50];
    printf("请输入中缀表达式， 以 = 作为结束标志：\n");
    scanf("%s",s);
    zhong_revert_hou(s);
    calculate();
    return 0;
}
