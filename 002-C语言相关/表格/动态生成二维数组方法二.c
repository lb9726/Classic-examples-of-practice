#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h> 
main() 
{ 
	int i = 0; 
	int j = 0; 
	int line = 0; 
	int row = 0; 
	int **p = NULL; 

	printf("input the line of the array:\n"); 
	scanf("%d", &line); 
	printf("input the row of the array:\n"); 
	scanf("%d", &row); 

	p = (int **)malloc(sizeof(int *) * line); 
	if (NULL == p) 
	{ 
		return; 
	} 
	for (i = 0; i < line; i++) 
	{ 
		*(p + i) = (int *)malloc(sizeof(int) * row); 
		if (NULL == *(p + i)) 
		{ 
			return; 
		} 
	} 
	
	/*input data*/ 
	
	for (i = 0; i < line; i++) 
	{ 
		for(j = 0; j < row; j++) 
		{ 
			p[i][j] = i + 1; 
		} 
	} 
	
	/*output data*/ 
	
	for (i = 0; i < line; i++) 
	{ 
		for(j = 0; j < row; j++) 
		{ 
			printf("%d ", p[i][j]); 
		} 
	} 
	
	/*free every line point*/ 
	
	for (i = 0; i < line; i++) 
	{ 
		free(*(p + i)); 
		p[i] = NULL; 
	} 

	free(p); 
	p = NULL; 
}



