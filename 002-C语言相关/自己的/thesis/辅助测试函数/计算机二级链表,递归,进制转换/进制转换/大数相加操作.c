/*
利用字符串接受两个大数，把两个数字相加输出。
两个数字均不超过 20位
输入：123456789123
              1238
输出：123456790361
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define N 30

//将字符串转成数组
void convertstringtoshuzu(char *p,char *q,int a[],int b[])
{
    int i=0,j=0;
    while(*p!='\0')
    {
        a[i++]=*p-'0'; 
        p++;  
    }
    while(*q!='\0')
    {
        b[j++]=*q-'0'; 
        q++;  
    }
}

//实现两个数组相加
void addtwoshuzu(int a[],int b[],int c[],int n,int k)
{
    int i=0,j,count=0;
    for(i=n-1,j=k-1;i!=-1&&j!=-1;i--,j--) //第一个for是处理c[i]的值的,即是把c[i+1]=a[i]+b[j]中c[i+1]的值计算出来
    {                                     //第一步不管c[i]的值是否大于10,仅仅是将c[i]存起来而已,下一步处理大于10的情况
        if(n>=k)
            {
                c[i+1]=a[i]+b[j];    
            }        
        else
            {
                c[j+1]=a[i]+b[j];
            }
    }
    printf("j=%d\n",j);
    printf("i=%d\n",i);
    if(n<k)
    {
        for(;j>=0;j--)  
        {
            c[j+1]=b[j];
        }
    }//printf("j=%d\n",j);
    else
    {
        for(;i>=0;i--)
        {
            c[i+1]=a[i];
        }
    }//printf("i=%d\n",i);
//处理c[i]大于10的数
    if(n>=k)
    {   c[0]=0;
        for(i=n;i>=0;i--)
        {
            if(c[i]>=10)
            {
               c[i]-=10;
               i--;
               c[i]=c[i]+1;
               i++;
            }
            printf("c[%d]=%d\n",i,c[i]);
        }
    }
    else  //处理c[i]大于10的数
    {   c[0]=0;
        for(j=k;j>=0;j--)
        {
            if(c[j]>=10)
            {
               c[j]-=10;
               j--;
               c[j]=c[j]+1;
               j++;
            }
            printf("c[%d]=%d\n",j,c[j]);
        }
    }
}

int main()
{
    int a[N],b[N],c[N],i,n,k,w;
    char s[N],t[N];
    printf("请输入一串首位不为0的数 :");
    scanf("%s",s);
    printf("请再输入一串首位不为0的数 :");
    scanf("%s",t);
    n=strlen(s);
    k=strlen(t);
    convertstringtoshuzu(s,t,a,b);printf("\n");
    printf("您输入第一组的数据为 :");
    for(i=0;i<n;i++)
        printf("%d",a[i]);
    printf("\n");
    printf("您输入第二组的数据为 :");
    for(i=0;i<k;i++)
        printf("%d",b[i]);
    printf("\n");
    addtwoshuzu(a,b,c,n,k);
    printf("相加后的数据为: ");
    if(n>=k)
    {
        if(c[0]==0)
            w=1;
        else
            w=0;
        for(i=w;i<=n;i++)

            printf("%d",c[i]);
    }
    else
    {
        if(c[0]==0)
            w=1;
        else
            w=0;
        for(i=w;i<=k;i++)
            printf("%d",c[i]);
    }
    printf("\n");
    return 0;
}
