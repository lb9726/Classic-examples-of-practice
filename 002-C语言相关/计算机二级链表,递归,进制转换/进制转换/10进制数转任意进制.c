#include<stdio.h>
#include<stdlib.h>
int  convert(int a[],int n,int R)
{
	int k=0;
	while(n)
	{
		a[k++]=n%R;
		n=n/R;
	}
	return k;
}

int main()
{
	int a[33],n,R,k,i;
	printf("请输入您想要转换的数和相应的进制:");
	scanf("%d%d",&n,&R);
	k=convert(a,n,R);
	printf("10进制的%d对应的%d进制数为:",n,R);
	for(i=k-1;i>=0;i--)
		printf("%d",a[i]);
	printf("\n");
	return 0;
}


