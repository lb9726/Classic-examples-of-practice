#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 15
#define NUM 5
int strFlag = 0;
typedef struct Flag
{
	int num;
	int counts;
}Arr_FLag; 

void init_arr(Arr_FLag a[])
{
	int i;
	for(i = 0; i < N; i++)
	{
		a[i].num = i;
		a[i].counts = 0;
	}
}

void convert_enter(char *str)
{
	char *p = str;
	while( '\n' != *p)
	{
		p++;
	}
	*p = '\0';
}

int judge_input(char *str)
{
	int flag = 0;
	char *p = str;
	while(*p != '\n')
	{
		if (*p != 'J' && *p != 'Q' && *p != 'K' && *p != 'A' 
			&& *p != ','&& (*p < '0' || *p > '9'))
		{
			flag = 1; printf("*p = %c\n",*p);
			return flag;
		}
		p++;
	}
	return flag;
}

int get_input_num(char a[])
{
	char *p = a;
	int sum = 0;
	int t = 0;
	while(*p)
	{
		if ('J' == *p)
		{
			sum = 11;
		}
		else if ('Q' == *p)
		{
			sum = 12;
		}
		else if ('K' == *p)
		{
			sum = 13;
		}
		else if ('A' == *p)
		{
			sum = 14;
		}
		else
		{
			sum = sum *10 + *p - '0';
//			sum = sum + t;
		}
		p++;
	}
	printf("sum = %d\n",sum);
	return sum;
}

void deal_input(char *str, int *result)
{
	char *p = str;printf("str = %s\n", str);
	char *s;
	char a[3];
	int i = 0;
	int j = 0;
	while(*p)
	{
		if (*p != ',' && ' ' != *p || *s == '\0') // 最后一个字符存入数组时，需要加上结束符
		{
			a[i++] = *p; 
			a[i] = *s; // 把\0存入a字符串中，作为结束符
			if (*s == '\0')
			{
				result[j++] = get_input_num(a);
			}
			printf("deal_input *p = %c\n",*p);
			if (0 != strcmp(a,"10"))
			{
			    strFlag = 1;
			}
		}
		else
		{
			if (*p != ' ' || *p == '\0')
			{
				a[i] = '\0'; printf("a = %s\n", a);
				i = 0;
				result[j++] = get_input_num(a);  //将一位或多位数的字符串转化为int数字存入result数组中
				if (0 != strcmp(a,"10"))    // 如果用户输入的两位数不为10的话，则表示输入错误
			    {
			        strFlag = 1;
			    }
			}
		}
		p++;
		s = p + 1;  // s多比p往后多访问一个字符
	}
	int t;
	for(t = 0; t < j; t++)
	{
		printf("result[%d] = %d\n",t,result[t]);
	}
	printf("strFlag = %d\n", strFlag);
}

void exchange_position(Arr_FLag a[N])
{
	Arr_FLag temp;
	int i,j;
	for(i = 0; i < N; i++)
	{
		for (j = i; j < N ; j++)
		{
			if (a[i].counts <= a[j].counts)
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	for(i = 0; i < N; i++)
	{
		printf("a[%d] = %d, counts = %d\n", i, a[i].num, a[i].counts); 
	}
}

void print(Arr_FLag a[N])
{
	int i;
	int sum = 0;
	for(i = 0; i < N - 1; i++)
	{
		if (a[i].counts > 0)
		{
			int t = a[i].counts;  // t为多少就打印a[i]多少次
			while(t--)
			{
				sum ++;
				if (sum < NUM )
				{
				    if (11 == a[i].num)
				        printf("%c,", 'J');
				    else if (12 == a[i].num)
				        printf("%c,", 'Q');
				    else if (13 == a[i].num)
				        printf("%c,", 'K');
				    else if (14 == a[i].num)
				        printf("%c,", 'A');
				    else 
					    printf("%d,",a[i].num);
				}
				else 
				{
				    if (11 == a[i].num)
				        printf("%c", 'J');
				    else if (12 == a[i].num)
				        printf("%c", 'Q');
				    else if (13 == a[i].num)
				        printf("%c", 'K');
				    else if (14 == a[i].num)
				        printf("%c", 'A');
				    else 
					    printf("%d", a[i].num);
			    }
			}
		}		
	}
}

void user_input(char *str)
{
	printf("请输入扑克牌的数字或字母，例如：2,3,5,J,Q\t:\n");
	fgets(str, 49, stdin);
	while (judge_input(str) || strFlag) // 判断用户输入是否合法
	{
		printf("input error please input again!");
		fgets(str, 49, stdin);
	}
}
/*对用户输入的结果计数，统计哪张牌出现的次数*/
void set_counts(Arr_FLag a[N], int result[])
{
	int i,j;
	for(i = 0; i < NUM; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (result[i] == a[j].num)
			{
				a[j].counts++;
			}
		}
	}
	for(i = 0; i < N; i++)
	{
		printf("a[%d] = %d, counts = %d\n", i, a[i].num, a[i].counts); 
	}
}

int main()
{
	Arr_FLag a[N];
	char str[50];
	int result[NUM] = {0};
	init_arr(a);
	user_input(str);
	convert_enter(str);
	deal_input(str, result);
	set_counts(a, result);
	exchange_position(a);
	print(a);
	printf("\n");
	return 0;
}

















