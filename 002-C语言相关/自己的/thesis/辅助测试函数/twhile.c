#include<stdio.h>
#include<stdlib.h>

//处理键盘输入字符的函数，返回值为int型的
int inputdigit(char li,char left,char right)
{
	char ch[30];
	printf("请输入操作选项：%c 到 %c之间的数字!!\n",left,right);
	
	do
	{
		fgets(ch,29,stdin);
		li = ch[0];
		rewind(stdin);/*清空键盘缓冲区里的无用字符*/
		if(!(li >= left && li <= right))
			printf("\033[;31m您输入的选项有误，请重新输入!!\033[0m\n");
	}
	while(!(li >= left && li <= right));
	return li-'0';
}

int main()
{
	char li;
	int n = inputdigit(li,'0','9');
	if(n == 0)
		printf("n = %d\n",n);
	else 
		printf("n = %d\n",n);
	return 0;
}
