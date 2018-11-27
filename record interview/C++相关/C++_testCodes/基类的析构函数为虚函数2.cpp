#include<iostream>
using namespace std;
class ClxBase{
public:
    ClxBase() {};
    ~ClxBase() {cout << "Output from the destructor of class ClxBase!" << endl;};

    void DoSomething() { cout << "Do something in class ClxBase!" << endl; };
};

class ClxDerived : public ClxBase{
public:
    ClxDerived() {};
    ~ClxDerived() { cout << "Output from the destructor of class ClxDerived!" << endl; };

    void DoSomething() { cout << "Do something in class ClxDerived!" << endl; }
};
int   main()
{  
  ClxBase *p =  new ClxDerived;
  p->DoSomething();
  delete p;
  return 0;
} 

/*
Do something in class ClxBase!
Output from the destructor of class ClxBase!

这段代码中基类的析构函数同样不是虚函数,不同的是在main函数中用基类的指针去操作继承类的成员,释放指针P的过程是:只是释放了基类的资源,而没有调用继承类的析构函数.调用　　dosomething()函数执行的也是基类定义的函数.
    一般情况下,这样的删除只能够删除基类对象,而不能删除子类对象,形成了删除一半的对象,造成内存泄漏.
    在公有继承中,基类对派生类及其对象的操作,只能影响到那些从基类继承下来的成员.如果想要用基类对非继承成员进行操作,则要把基类的这个函数定义为虚函数.

    析构函数自然也应该如此:如果它想析构子类中的重新定义或新的成员及对象,当然也应该声明为虚的.
*/





