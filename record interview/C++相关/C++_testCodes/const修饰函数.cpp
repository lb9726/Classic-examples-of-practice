#include<iostream>
using namespace std;

class A
{
private:
    int i;
public:
    void set(int n) //set函数需要设置i的值，所以不能声明为const 
    {
        i = n;
    }
    
    int get()const //get函数返回i的值，不需要对i进行修改，则可以用const修饰。防止在函数体内对i进行修改。
    {
//        i = 8;  // st$ g++ const修饰.cpp -o c
//const修饰.cpp: In member function ‘int A::get() const’:
//const修饰.cpp:16:13: error: assignment of member ‘A::i’ in read-only object

        return i;
    }
};

int main()
{
    A a;
    int i = 6;
    a.set(i);
    a.get();
    cout << "i = "<< i << endl;
    return 0;
}
