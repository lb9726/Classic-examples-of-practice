#include<iostream>
using namespace std;
class ClxBase{
public:
    ClxBase() {};
    virtual ~ClxBase() {cout << "Output from the destructor of class ClxBase!" << endl;};
    virtual void DoSomething() { cout << "Do something in class ClxBase!" << endl; };
};

class ClxDerived : public ClxBase{
public:
    ClxDerived() {};
    ~ClxDerived() { cout << "Output from the destructor of class ClxDerived!" << endl; };
    void DoSomething() { cout << "Do something in class ClxDerived!" << endl; };
};

int  main()
{  
  ClxBase *p =  new ClxDerived;
  p->DoSomething();
  delete p;
  return 0;
}  

/*
Do something in class ClxDerived!
Output from the destructor of class ClxDerived!
Output from the destructor of class ClxBase!

这段代码中基类的析构函数被定义为虚函数,在main函数中用基类的指针去操作继承类的成员,释放指针P的过程是:只是释放了继承类的资源,再调用基类的析构函数.调用dosomething()函数执行的也是继承类定义的函数.  

    如果不需要基类对派生类及对象进行操作,则不能定义虚函数,因为这样会增加内存开销.当类里面有定义虚函数的时候,编译器会给类添加一个虚函数表,里面来存放虚函数指针,这样就会增加类的存储空间.所以,只有当一个类被用来作为基类的时候,才把析构函数写成虚函数.

    析构函数自然也应该如此:如果它想析构子类中的重新定义或新的成员及对象,当然也应该声明为虚的.
*/













