#include<iostream>
using namespace std;

class O
{
public:
	void F2()
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
	void F3()
	{
		cout << "is F3" << endl;
	}
};

class Q :public  P
{
};

int main()
{
	P p;
//	p.F1();
	p.F2();
	
	Q q;
//	q.F1();
	q.F2();
	q.F3();
	return 0;
}







