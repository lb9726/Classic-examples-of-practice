#include<iostream>  
using namespace std;  
  
class A  
{  
public:  
    void foo()  
    {  
        cout<<"1\n";  
    }  
    virtual void fun()  
    {  
        cout<<"2\n";  
    }  
};  
class B : public A  
{  
public:  
    void foo()  
    {  
        cout<<"3\n";  
    }  
    void fun()  
    {  
        cout<<"4\n";  
    }  
};  
int main(void)  
{  
    A a;  
    B b;  
    A *p = &a;  
    p->foo();  //调用基类的打印出 1
    p->fun();  //调用基类的打印出 2
    p = &b;  
    p->foo();  //调用基类的打印出 1
    p->fun();  //调用子类的打印出4
    return 0;  
}

/*
 第一个p->foo()和p->fuu()都很好理解，本身是基类指针，指向的又是基类对象，调用的都是基类本身的函数，因此输出结果就是1、2。
 　  第二个输出结果就是1、4。p->foo()和p->fuu()则是基类指针指向子类对象，正式体现多态的用法，p->foo()由于指针是个基类指针，指向是一个固定偏移量的函数，因此此时指向的就只能是基类的foo()函数的代码了，因此输出的结果还是1。而p->fun()指针是基类指针，指向的fun是一个虚函数，由于每个虚函数都有一个虚函数列表，此时p调用fun()并不是直接调用函数，而是通过虚函数列表找到相应的函数的地址，因此根据指向的对象不同，函数地址也将不同，这里将找到对应的子类的fun()函数的地址，因此输出的结果也会是子类的结果4
*/





