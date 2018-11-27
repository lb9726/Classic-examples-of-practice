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
			while ('(' != e)       //比较栈顶元素是不是左括号
			{
				printf("%c ",e);   // 出栈时打印数据
				string[li++] = e;
				string[li++] = ' ';
				Pop(&s,&e);
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
  /*        if(StackLen(s))
            {
                Pop(&s,&e);
                while(StackLen(s) && '(' != e && '+' !=e && '-' != e)
                {
                    printf("%c ",e);
                    string[li++] = e;
                    string[li++] = ' ';
                    Pop(&s,&e);
                }
                Push(&s,e);
            }
            Push(&s,c);*/
            if (!StackLen(s)) 
            {
                Push(&s,c); //如果栈为空，则入栈
            }
            else
            {
                Pop(&s,&e); //否则先出栈
                while(StackLen(s) && '(' != e)
                {
                    printf("%c ",e);
                    string[li++] = e;
                    string[li++] = ' ';
                    Pop(&s,&e);
                }
                if ('(' == e)
                {
                    Push(&s,e);
                }
                Push(&s,c);
            }
            
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
	//printf("\n 最终的计算结果为：%f\n",d);
	string[li]= '=';
	return 0;
}




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
	return 0;
}


/*
测试用例：
1*2/3=
((3.5*2-4.5+0.5)*8)+(9/5)*4=
12*(6-3)+6/2*3
(1-2)*(4+5)#
4.6-(-3/4+1.6-4-3/4)=
*/






