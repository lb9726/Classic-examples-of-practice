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
	return 0;
}
