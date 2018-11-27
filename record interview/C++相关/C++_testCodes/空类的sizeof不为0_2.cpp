//#charles#下列是例子
#include <iostream>
using namespace std;

class a 
{
};

class b1
{
};

class b
{
    char a;
};

class c:public a
{
    virtual void fun() = 0;
};

class d:public b, public c
{
};

class e:public b1, public c
{
};

class f:public c, public b
{
};

int main()
{
    cout<<"sizeof(a) = "<<sizeof(a)<<endl;
    cout<<"sizeof(b) = "<<sizeof(b)<<endl;
    cout<<"sizeof(c) = "<<sizeof(c)<<endl;
    cout<<"sizeof(d) = "<<sizeof(d)<<endl;//#这种情况是8
    cout<<"sizeof(e) = "<<sizeof(e)<<endl;//#这种情况是4
    cout<<"sizeof(f) = "<<sizeof(f)<<endl;
    return  0;
}











