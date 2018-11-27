#include <iostream>
 
using namespace std;
 
int main()
{
int c[4]={1,2,3,4};
int *a[4]; //指针数组
int (*b)[4]; //数组指针
b=&c;
//将数组c中元素赋给数组a
for(int i=0;i<4;i++)
{
    a[i]=&c[i];
    cout<<*a[i]<<endl; //输出2就对
}
cout<<endl;
//将数组c中元素赋给数组a
for(int i=0;i<4;i++)
{
    *a[i] = c[i];
    cout<<*a[i]<<endl; //输出2就对
}

cout<<endl;
//输出看下结果
cout<<*a[1]<<endl; //输出2就对
cout<<(*b)[2]<<endl; //输出3就对
return 0;
}

