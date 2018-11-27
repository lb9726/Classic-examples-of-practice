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

    void DoSomething() { cout << "Do something in class ClxDerived!" << endl; };
};

int   main()
{  
  ClxDerived *p =  new ClxDerived;
  p->DoSomething();
  delete p;
  return 0;
}

/*
Do something in class ClxDerived!
Output from the destructor of class ClxDerived!
Output from the destructor of class ClxBase!

这段代码中基类的析构函数不是虚函数,在main函数中用继承类的指针去操作继承类的成员,
释放指针P的过程是:先释放继承类的资源,再释放基类资源. 
*/





