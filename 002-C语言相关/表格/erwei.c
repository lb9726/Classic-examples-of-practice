#include<stdio.h>
#include<malloc.h>
int  main()
{
	int column,row;
	int **array;
	printf("输入行和列（输入行后，用“ ”隔开，然后输入列）：\n");
	scanf("%d %d",&column,&row);
	array = (int **)malloc(sizeof(int *)*row);
	for (int i = 0;i != row; i++)
		array[i]=(int *)malloc(sizeof(int)*column);
	for (int j=0; j != row; j++)
	{
		for (int k = 0; k !=column; k++)
		{
			scanf("%d",&array[j][k]);
		}
	}
	
	for (int m = 0;m < row; m++)
	{
		for (int n = 0;n < column; n++)
		{
			printf("%-3d",array[m][n]);
		}
	}
	printf("\n");
	return 0;
}
