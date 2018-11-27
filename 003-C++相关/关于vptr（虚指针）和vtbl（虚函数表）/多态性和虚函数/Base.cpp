#include<iostream>
using namespace std;

class BASE
{
	int bx;
public:
	BASE(int b)
	{
	    bx = b;
	}
	void display()
	{
	    cout<<"BASE:"<<bx<<endl;
	}
	void inc()
	{
	    ++bx;
	}
};

class INHERITED: public BASE
{
    int dx;
public:
    INHERITED(int b, int d):BASE(b), dx(d)
    {
    }
    void display()
    {
        cout <<"INHERITED:"<<dx<<endl;
    }
    void inc()
    {
        ++dx;
    }
};


void func(BASE& Obj)
{
    Obj.inc();
    Obj.display();
}

int main()
{
    BASE baseobj(5);
    BASE * bp;
    INHERITED iobj(1, 15);
    cout<<"指针引用"<<endl;
    bp = &baseobj;
    bp->display();
    bp = &iobj;
    bp->display();
//    ip = &baseobj; // 错误，子类指针不能指向父类对象
//    ip->display();

    
    cout<<"对象引用"<<endl;
    baseobj.display();
    iobj.display();
    cout<<"函数调用"<<endl;
    func(baseobj);
    func(iobj);
    return 0;
}

/*
指针引用
BASE:5
BASE:1
对象引用
BASE:5
INHERITED:15
函数调用
BASE:6
BASE:2

*/

/*
分析程序的运行结果，我们可知，通过指针调用成员函数只与指针类型有关，于此刻指向的对象无关。基类指针无论指向基类对象还是派生类对象，利用bp->display();调用的都是基类的成员函数display()。若要调用派生类中的成员函数，display()必须通过对象来调用，或定义派生类指针来实现。这种通过用户
自己指定调用成员函数（如iobj.display()),在编译时根据类对象来确定调用该类的成员函数的方式，是静态联编。另外，在给func()函数传递的无论是基类BASE的对象baseobj还是INHERITED 的对象，执行的结果都为BASE：6, 而不是BASE:6与INHERITED：16.显然这个结果不是我们期望的结果。这是由于采用了静态联编的方式，即编译器在编译时已将func函数中的inc()和display()与BASE类的inc()成员函数和display()成员函数相关联的结果。
解决这一问题的办法就是将确定函数体和函数调用的联系推迟到运行时，即采用动态联编方式。在C++中，为了使特定函数进行动态联编，要求在基类声明这个函数时使用virtual关键字，此函数也就称为虚函数。
*/

/*
联编是指将函数调用与相应的函数代码彼此相关联的过程。如果联编在编译阶段完成，称之为静态联编。重载函数就是静态联编的方式。因为虽然两个函数具有相同的函数名，但由于其参数类型不同，编译程序可以据此来自动选择对应的函数体进行匹配，也就是说重载函数可以在编译时期确定调用哪个函数，因此称为静态联编。

在C++中还有一种联编方式称为动态联编。这种方式是在程序运行时进行联编，即当程序调用到某一函数名时，才去寻找和连接其程序代码，一般通过函数指针或引用来实现。

*/








