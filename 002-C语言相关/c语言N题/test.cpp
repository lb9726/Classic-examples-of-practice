#include<iostream>
#include<stdio.h>
using namespace std;

class b
{
	public:
		void t(int i);
};


class a:public b
{
	public:
		void t(int i);
		void libo(int i,int j);
};


void a::libo(int i,int j)
{
	cout << i <<"  "<< j << endl;
	printf("%s\n",__PRETTY_FUNCTION__);
    b::t(6);
}

void a::t(int i)
{
	//cout << __PRETTY_FUNCTION__<< endl;
	this->libo(i,2);
	cout << __PRETTY_FUNCTION__<< endl;
}

void b::t(int i)
{
	cout << __PRETTY_FUNCTION__<< endl;
	cout << i <<endl;
}

int main()
{
	a tc;
	b tt;
	tt.t(2);
	tc.t(1);
	cout << __PRETTY_FUNCTION__ << endl;
	return 0;
}
