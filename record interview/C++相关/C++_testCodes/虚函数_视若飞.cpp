#include<iostream>
using namespace std;

class A
{
public:
	virtual void fun(int a = 1) 
	{
		cout <<" A->" << a << endl;
	}
	
	virtual void test()
	{
		fun();
	}
};

class B:public A
{
public:
	virtual void fun(int a = 0)
	{
		cout << "B->"<< a <<endl;
	}
};


int main()
{
	B *p = new B;
	p->test();
	p->fun();
	delete p;
	return 0;
}

/*
运行结果为：
B->1
B->0
考察点，是虚函数
因为B重写了A父类的fun的虚函数，
重写(覆盖)：是指派生类中存在重新定义的函数。其函数名，参数列表，返回值类型，所有都必须同基类中被重写的函数一致。只有函数体不同（花括号内），派生类调用时会调用派生类的重写函数，不会调用被重写函数。重写的基类中被重写的函数必须有virtual修饰。

而B没有test的函数，所以调用test函数时会调用父类的test函数，
而父类的test函数有调用父类的fun函数，fun函数被B重写了，因此
调用的是B的fun，而test函数并不能直接访问B的a，随意a为1,不为0
*/











