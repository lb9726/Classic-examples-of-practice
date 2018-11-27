/*
使用穷举法求取多个数的最大公约数,取到生成的数当中的最小值，依次做--操作，直到取余所有数都为0的时候
即为最大公约数
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define N 10

/*初始化数组*/
void array_init(int a[], int num);

/*自动随机生成数值*/
void autocreatenum(int a[], int num);

/*取得数组中的最小值*/
int get_min_num(int a[], int num);

/*使用穷举法获得最大公约数*/
int get_Maxgongyueshu(int a[], int remain[], int num);


/*初始化数组*/
void array_init(int a[], int num)
{
    int i;
    for(i = 0; i < num; i++)
    {
        a[i] = 1;
    }
}

/*自动随机生成数值*/
void autocreatenum(int a[], int num)
{
	int i;
	srand(time(NULL));
	for(i = 0; i < num; i++)
	{	
	    a[i] = rand()%1000;
	}
}

/*取得数组中的最小值*/
int get_min_num(int a[], int num)
{
    int i;
    int min = a[0];
    for(i = 1; i < num; i++)
    {
        if(min > a[i])
        {
            min = a[i];
        }
    }
    printf("min = %d\n", min);
    return min;
}

/*使用穷举法获得最大公约数*/
int get_Maxgongyueshu(int a[], int remain[], int num)
{
    int i, j, m, flag;
    int min_in_arr = get_min_num(a, num);
    
    for(j = min_in_arr; j > 1; j--)
    {
        for(i = 0; i < num; i++)   // 先计算余数    
        {
            remain[i] = a[i] % j;
        }
        
        for(m = 0; m < num; m++)   // 然后判断余数
        {
            if (0 != remain[m])    // 只要余数中有一个不为0,则不是最大公约数
            {
               flag = 1;
               break;
            }
            else 
            {
                flag = 0;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
    printf("最大公约数 j = %d\n", j);
    return j;
}
void print(int a[], int num)
{
    int i;
    for (i = 0; i < num; i++)
    {
        if (i < num -1)
        {
            printf("%d,", a[i]);
        }
        else
        {
            printf("%d ", a[i]);
        }
    }
}

int main()
{
    int a[N] = {6,8,120,8,12,16,20,24,32,32};
    int b[N];
    //autocreatenum(a, N);

    array_init(b, N);
    int max = get_Maxgongyueshu(a, b, N);
    print(a, N);
    printf("的最大公约数为：%d\n", max);
    return 0;
}

















