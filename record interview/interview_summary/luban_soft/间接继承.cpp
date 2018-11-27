#include<iostream>
using namespace std;

class O
{
public:
	virtual void F2()
	{
		cout << "is F2 " << endl;
	}
private:
	void F1()
	{
		cout << "is F1 " << endl;
	}
};

class P : public  O
{
public:
	virtual void F2()
	{
		cout << "is P F2" << endl;
	}
	virtual void F3()
	{
		cout << "is F3" << endl;
	}
};

class Q :public  P
{
public:
	void F2()
	{
		cout  << " is Q F2 " << endl;
	}
	void F3()
	{
		cout  << " is Q F3 " << endl;
	}
};

int main()
{
	 P *p = new Q;
	p->F2();
	p->F3();
	
	O *o = new Q;
	o->F2();
	return 0;
}







