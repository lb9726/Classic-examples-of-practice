#include <iostream>
using namespace std;

class A 
{ 
};

class B 
{
    char ch;
    void func() { }
};

class C 
{
    char ch1; //占用1字节
    char ch2; //占用1字节
    virtual void func() { }
};

class D 
{
    int in;
    virtual void func() { }
};

int main() 
{
    A a;
    B b;
    C c;
    D d;
    cout<<sizeof(a)<<endl;//result=1   
    cout<<sizeof(b)<<endl;//result=1   //对象c扩充为2个字，但是对象b为什么没扩充为1个字呢（空类的对象一个字节，含一个char的类类对象也为一个字节。）？因为B类只有一个成员变量，普通成员函数不占用内存。
    cout<<sizeof(c)<<endl;//result=8   
    //对象c实际上只有6字节有用数据，但是按照上面第二点编译器优化，编译器将此扩展为两个字（add charles 字节对齐），即8字节
    cout<<sizeof(d)<<endl;//result=8   
}

/*
运行结果：64位操作系统
1  空的类的对象为1
1  普通成员函数不占用内存。
16  对于具有虚函数的类型来说，需要有一个方法为它的实体提供类型信息(RTTI)和虚函数入口，常见的方法是建立一个虚函数入口表，这个表可为相同类型的对象共享，因此对象中需要有一个指向虚函数表的指针 ch1 为1, ch2 为1,加上虚函数的指针8,所以前面的2,需要补足6个字节，总共16
16  int in为4,后面的指针为8,最终内存对齐的为16  
*/









