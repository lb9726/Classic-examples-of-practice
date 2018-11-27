#include <string>
using namespace std;
/*
    C++允许 重载函数调用操作符，可以写作operator()。
    如果为类编写一个operator(),就可以将该类的对象作为函数指针来使用。
    只能把这个操作符重载为类中的一个非静态方法。以下是一个简单的类，
    其中有一个重载的operator(),还有一个有相同行为的类方法：
*/

class FunctionObject
{
public:
    int operator() (int inParam); // function-call operator
    void operator() (string& str) {}
    int aMethod(int inParam); // normal method
};

//Implementation of overloaded function-call operator
int FunctionObject::operator() (int inParam)
{
    return (inParam * inParam);
}

// Implementation of normal method
int FunctionObject::aMethod(int inParam)
{
    return (inParam * inParam);
}

int main(int argc, char** argv)
{
    int x = 3, xSquared, xSquaredAgain;
    FunctionObject square;

    xSquared = square(x); // Call the function-call operator
    xSquaredAgain = square.aMethod(x); // Call the normal method

    return (0);
}

