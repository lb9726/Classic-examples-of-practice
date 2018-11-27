#include<stdio.h>
#include<stdlib.h>
#define N 41
#define M 3

int main()
{
	int man[N] = {0};
	int count = 1;
	int i = 0, pos = -1;
	int alive = 0;
	while(count <= N)
	{
		do{
			pos = (pos + 1) % N;//环状处理
			printf("pos = %d\n",pos);
			if(man[pos] == 0)
				i++;
			if(i == M) //报数为3的人
			{
				i = 0;
				break;
			}
		}while(1);
		man[pos] = count;
		count ++;printf("count = %d\n",count);
	}
	
	printf("\n约瑟夫排列(最初位置-约瑟夫位置):\n");
	for(i = 0; i < N; i ++)
	{
		printf("%-d-%-3d",i+1,man[i]);
		if(i != 0 && i%10 == 0) //每输出10个换行
			printf("\n");
	}
	printf("\n\n准备剩下的人数?");
	scanf("%d",&alive);
	printf("这%d的人的初始位置应排在一下序号：\n",alive);
	alive = N - alive;
	for( i = 0; i < N ; i++)
		if(man[i] > alive)
			printf("初始化序号：%d,约瑟夫环序号:%d\n",i+1,man[i]);
	printf("\n");
	getchar();
	return 0;		
}


















