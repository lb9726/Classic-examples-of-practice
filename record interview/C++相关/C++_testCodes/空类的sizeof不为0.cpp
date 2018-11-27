#include<iostream>
using namespace std;
class a 
{
};
class b
{
};
class c:public a
{
    virtual void fun() = 0;
};

class d:public b, public c
{
};
int main()
{
    cout<<"sizeof(a) = "<<sizeof(a)<<endl;
    cout<<"sizeof(b) = "<<sizeof(b)<<endl;
    cout<<"sizeof(c) = "<<sizeof(c)<<endl;
    cout<<"sizeof(d) = "<<sizeof(d)<<endl;
    return  0;
}

/*
程序执行的输出结果为：
sizeof(a) =1
sizeof(b) = 1
sizeof(c) = 4
sizeof(d) = 8 
#charlse# 这里错误，这个调试中是4
*/

