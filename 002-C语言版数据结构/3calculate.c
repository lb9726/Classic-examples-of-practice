#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include<ctype.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define MAXBUFFER 10

char string[50];

typedef char ElemType;
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack;

typedef double bElemType;
typedef struct
{
	bElemType *base;
	bElemType *top;
	int stackSize;
}bsqStack;

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
	*(s->top) = e;// 给当前的栈顶赋值
	s->top++; // 然后栈顶元素加一
}

void Pop(sqStack *s, ElemType *e)
{
	if (s->top == s->base)
	{
		return ;
	}
	*e = *--(s->top); // 出栈时栈顶先减一再取当前的栈顶的元素给e
}


// 有的时候用指针，有的时候用不用指针，一般对内容修改的用指针，其余的不用指针
int StackLen(sqStack s)
{
	return (s.top - s.base);
}




void bInitStack(bsqStack *s)
{
	s->base = (bElemType *)malloc(STACK_INIT_SIZE * sizeof(bElemType));
	if (!s->base)   //如果分配失败退出程序
	{
		exit(0);
	}
	s->top = s->base;  //栈的初始化时栈顶和栈底指向同一个地址
	s->stackSize = STACK_INIT_SIZE;
}

void bPush(bsqStack *s, bElemType e)
{
    //如果栈已经满了则再追加空间
	if (s->top - s->base >= s->stackSize)
	{
		 s->base = (bElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) *sizeof(bElemType));
		 if(!s->base) //如果分配失败退出程序
		 	exit(0);	 
	}
	*(s->top) = e;
	s->top++;
}

void bPop(bsqStack *s, bElemType *e)
{
	if (s->top == s->base)
	{
		return ;
	}
	*e = *--(s->top);
}


// 有的时候用指针，有的时候用不用指针，一般对内容修改的用指针，其余的不用指针
int bStackLen(bsqStack s)
{
	return (s.top - s.base);
}
/*
DestroyStack(sqStack *s)
{
    int i ,len;
    len = s->stackSize;printf("len = %d\n",len);
    for (i=0; i<len ;i++)
    {printf("333\n");
        free(s->base);printf("111\n");
        s->base++;printf("222\n");
    }
    s->base = s->top = NULL;
    s->stackSize = 0;
}

DestroyBStack(bsqStack *s)
{
    int i ,len;
    len = s->stackSize;
    for (i=0; i<len ;i++)
    {
        free(s->base);
        s->base++;
    }
    s->base = s->top = NULL;
    s->stackSize = 0;
}
*/
DestroyStack(sqStack *s)
{
    free(s->base);
    s->base = s->top = NULL;
    s->stackSize = 0;
}

DestroyBStack(bsqStack *s)
{
    free(s->base);
    s->base = s->top = NULL;
    s->stackSize = 0;
}

int zhong_revert_hou()
{
	sqStack s;
	char c,e;
	InitStack(&s);
		
	int li = 0;
	printf("请输入中缀表达式， 以 = 作为结束标志：\n");
	scanf("%c",&c);
	while (c != '=')
	{
		while (c >= '0' && c <= '9') // 处理连续数字
		{
			printf("%c",c);
			string[li++] = c;
			scanf("%c",&c);
			if ((c < '0' || c > '9') && '.' != c) // 不是数字才打印空格，使得中缀表达式数字之间有该有的空格,因为数字可以是多位数的
			{
				printf(" "); 
				string[li++] = ' ';
			}
			if ('.' == c)
			{
			    printf("%c",c);
			    string[li++] = c;
			}
		}
		if ( ')' == c)             // 如果输入为右括号，则表明栈中必定会有左括号
		{
			Pop(&s,&e);            // 栈中元素和左括号比较则出栈，直到遇到左括号
			while ('(' != e)      //比较栈顶元素是不是左括号
			{
				printf("%c ",e);   // 出栈时打印数据
				string[li++] = e;
				string[li++] = ' ';
				if (StackLen(s))
				{
				    Pop(&s,&e);
				}
				else
				{
				    break;
				}			
			}			
		}
		else if ( '+' == c || '-' == c)
		{
			if ( !StackLen(s))
			{
				Push(&s,c);// 如果栈为空，则将输入的符号入栈
			}
			else           // 不为空时，先出栈
			{
				do 
				{
					Pop(&s,&e);  // 通过pop得到当前栈顶元素的值
					if ('(' == e)
					{
						Push(&s,e);// 如果左括号再重新压栈
					}
					else        // 可能为+ - * / 这几种可能
					{
						printf("%c ",e);  //否则将栈内数据打印出来
						string[li++] = e;
						string[li++] = ' ';
					}
				}while(StackLen(s) && '(' != e);// 如果不为空并且不是左括号则继续出栈
				Push(&s,c);
			}
		}
		else if( '*' == c || '/' == c )
        {
            if(StackLen(s))
            {
                Pop(&s,&e);
                while('*' == e || '/' == e)  //当栈顶元素为* / 时则弹栈顶元素
                {
                    printf("%c ",e);
                    string[li++] = e;
                    string[li++] = ' ';
                    if (StackLen(s))
                    {
                        Pop(&s,&e);
                    }
                    else
                    {
                        break;
                    }
                }
                if ('(' == e || '+' == e || '-' == e)   // 当pop后刚好为（，+ - 均需要压栈
                {
                    Push(&s,e);
                }
            }
            Push(&s,c);
        }
        else if('('== c)
        {
            Push(&s,c);
        }
		else if ('=' == c)
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
		string[li++] = e;
        string[li++] = ' ';
	}
	printf("\n");
	string[li]= '\0';
	printf("%s \n",string);
	string[li]= '=';
	DestroyStack(&s);
	return 0;
}

/*
测试用例：
1*2/3=
(((3.5*2-4.5+0.5)*8)+(9/5)*4)-5= 31.2
12*(6-3)+6/2*3=   45  
(1-2)*(4+5)=   -9
4.6-(-3/4+1.6-4-3/4)=  暂时还不能处理带负号的数字
4.6-(3/4+1.6-4-3/4)=   7
*/


int main()
{
	bsqStack s;
	char c;
	double d,e;
	char str[MAXBUFFER];
	int i = 0;
	zhong_revert_hou();
	bInitStack(&s);
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
				return -1;
			}
			//scanf("%c",&c);
			c = *p++;
			if( c == ' ')
			{
				d = atof(str);
				bPush(&s,d);
				i = 0;
				break;
			}
		}
		switch(c)
		{
			case '+':
				bPop(&s,&e);
				bPop(&s,&d);
				bPush(&s,d+e);
				break;
			case '-':
				bPop(&s,&e);
				bPop(&s,&d);
				bPush(&s,d-e);
				break;
			case '*':
				bPop(&s,&e);
				bPop(&s,&d);
				bPush(&s,d*e);
				break;
			case '/':
				bPop(&s,&e);
				bPop(&s,&d);
				if ( e != 0)
				{
					bPush(&s,d/e);
				}
				else
				{
					printf("\nerror:除数不能为零！\n");
					return -1;
				}
				break;
		}
		//scanf("%c",&c);
		c = *p++;
	}
	bPop(&s,&d);
	printf("\n 最终的计算结果为：%f\n",d);
	DestroyBStack(&s);
	return 0;
}

/*    将中缀表达式（即标准形式的表达式）转换为后缀式。
1.当读到一个操作数时，立即将它放到输出中。输出到终端。
2.如果读到的为左圆括号时，由于左圆括号的优先级最高，栈顶的任何元素都不可能被左圆括号从栈中置换出来，因此无须判断栈是否为空，直接压栈。
3.当读到一个操作符（其中操作符可能为+ - * /） ,如果此时栈为空，则直接推入栈中;如果栈不为空时，则先pop栈顶元素，比较读到的操作符和栈顶元素的优先级。
4.置换规则：当读入的操作符比 Pop出的栈顶元素的优先级 低或相等时，则输出Pop出的操作符，继续循环，直到栈顶元素比读入的操作符运算级低或者遇到（，停止循环，将pop出的当前的操作符或（重新压栈，再将读入的操作符压栈
5.当读入）时，则Pop栈中元素，输出到终端，直到遇到（停止，（不需要打印到终端，（无需压栈
6.对4进行示例分析：当读入+ - 时，如果Pop的栈顶元素为（则重新压栈，如果是（或者栈为空，退出循环，否则Pop并输出所有操作符，因为+ - * / 的运算符都不比+ - 的运算符低
7.对读入的 * / 运算符，如果栈为空，直接压栈;否则Pop 栈顶元素，比较如果栈顶元素为 * 或 /时，循环pop并输出，当栈为空或栈顶元素不为 * 或 /时退出循环判断循环退出的原因，如果栈顶元素不为*或/时，即为( - + 时，重新压栈，再将当前读入的操作符压栈
*/

/*
目的：将中缀表达式（即标准形式的表达式）转换为后缀式。
例子：a+b*c+(d*e+f)*g转换成abc*+de*f+g*+
 
转换原则：
1.当读到一个操作数时，立即将它放到输出中。操作符则不立即输出，放入栈中。遇到左圆括号也推入栈中。
2.如果遇到一个右括号，那么就将栈元素弹出，将符号写出直到遇到一个对应的左括号。但是这个左括号只被弹出，并不输出。
3.在读到操作符时，如果此时栈顶操作符优先性大于或等于此操作符，弹出栈顶操作符直到发现优先级更低的元素位置。除了处理）的时候，否则决不从栈中移走"（"。操作符中，+-优先级最低，（）优先级最高。
4.如果读到输入的末尾，将栈元素弹出直到该栈变成空栈，将符号写到输出中。
 
解如下：
首先，读入a，并送到输出，然后+被读入并压入栈中。接下来b读入并送到输出，此时状态如下：
stack:                                        输出：a b
           +
back  top
接下来读入*，由于优先性比栈顶元素+大（原则3），因此被压入栈顶，接着读入c，并送到输出：
stack:                                      输出：a b c
        + *
back top
然后读入+，由于此时栈顶元素为*，优先级比+大，因此将*弹出，弹出后原来的+变成栈顶元素，由于+的优先性和当前读入的+优先性相等，因此也被弹出（原则3），最后将读入的+压入栈中。因此此时状态如下：
stack:                                       输出：a b c * +
            +
back  top
下一个读入的符号是（，由于具有最高优先级，因此将其放入栈中，然后读入d:
stack:                                       输出：a b c * + d
             + (
back     top
继续读入，此时读入*，除非处理），否则（决不弹出（原则3），因此*被压入栈中，接下来读入e,并送到输出：
stack:                                      输出：a b c * + d e
             + ( *
back        top
再往后读入的符号是+，将*弹出并输出。（原则3，与之前步骤相似），然后将+压入栈中，接着读入f并送到输出：
stack:                               输出：a b c * + d e * f
           + ( +
back       top
现在读入），因此弹出栈元素直到遇到“（”（原则2）：
stack:                                输出： a b c * + d e * f +
            +
back  top
下面又读入一个*，被压入栈中，然后读入g并输出：
stack:                                    输出： a b c * + d e * f + g
          + *
back   top
现在输入为空，弹出栈中所有元素：
stack :                                    输出： a b c * + d e * f + g * +
empty                                 
 
自此全部完成。（总结自数据结构与算法导论C语言版）

*/





