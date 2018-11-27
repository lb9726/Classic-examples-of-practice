#include "singleton.h"

int main()
{
	singleton* sgn = singleton::Instance();
	sgn->setnumber(10);
	cout << "sgn->a = "<< sgn->getnumber() << endl;
	singleton* sgn1 = singleton::Instance();
	cout << "sgn1->a = "<< sgn1->getnumber() << endl;
	delete sgn;
	return 0;
}
