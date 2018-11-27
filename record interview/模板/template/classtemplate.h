#ifndef CLASSTEMPLATE
#define CLASSTEMPLATE

#include <iostream>
using std::cout;
using std::endl;

template<typename T1, typename T2>
class myClass
{
private:
    T1 I;
    T2 J;
public:
    myClass(T1 a, T2 b);
    void show();
};


#endif // CLASSTEMPLATE

