#include "classtemplate.h"
template <typename T1, typename T2>
myClass<T1, T2>::myClass(T1 a, T2 b):I(a), J(b)
{

}

// show()
template <typename T1, typename T2>
void myClass<T1, T2>::show()
{
    cout << "I = "<< I <<", J = "<< J << endl;
}

/*
 * template <class type> ret-type func-name(parameter list)
{
   // 函数的主体
}
*/
