#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
int main()
{	
	//char *name[30] = "a技术部门哈wo";///(错）invalid initializer
	char *name[30];
	//name = (char *)malloc(sizeof(char *)*30);(错）error: incompatible types when assigning to type ‘char *[30]’ from type ‘char *’
    name[1] = (char *)malloc(sizeof(char *)*30); 
	strcpy(name[1],"哈哈哈哈和");
	int len = strlen(name[1]);
	printf("len = %d\n",len);
	return 0;
}
