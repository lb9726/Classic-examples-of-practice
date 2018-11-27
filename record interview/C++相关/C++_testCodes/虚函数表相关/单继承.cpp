#include <iostream>
#include <stdio.h>
using namespace std;

typedef void (*FUNC)();        //重定义函数指针，指向函数的指针
void PrintVTable(int* vTable)  //打印虚函数表
{
    if (vTable == NULL)
    {
        cout << "vTable is NULL" << endl;
        return;
    }
    cout << "虚函数表地址:" << vTable << endl;
    int  i = 0;
    for (; vTable[i] != 0; ++i)
    {
        printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
        FUNC f = (FUNC)vTable[i];
        f();         //访问虚函数
    }
    cout << endl;
}

class Base
{
public:
    virtual void fun1()
    {
        cout << "Base::func1()" << endl;
    }
    virtual void fun2()
    {
        cout << "Base::func2()" << endl;
    }
private:
    int b;
};
class Derive :public Base
{
public:
    virtual void fun1()           //重写基类虚函数,实现多态
    {
        cout << "Derive::func1()" << endl;
    }

    virtual void fun3()
    {
        cout << "Derive::func3()" << endl;
    }
    void fun4()
    {
        cout << "Derive::func4()" << endl;
    }
private:
    int d;
};


int main()
{
    Base b;
    Derive d;
    int* tmp = (int*)(*(int*)&b);     //取到虚函数的地址
    PrintVTable(tmp);
    int* tmp1 = (int*)(*(int*)&d);
    PrintVTable(tmp1);
}












