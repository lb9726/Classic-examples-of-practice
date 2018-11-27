#include <iostream>
using namespace std;
int main()
{
    int a = 123;
    auto f = [a] { cout << a << endl; }; 
    a = 321;
    f(); // 输出：123
}
/*
libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_NewFeature/Lambda表达式$ g++ 003_example.cpp -o 003 -std=c++11
libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_NewFeature/Lambda表达式$ ./003
123
libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_NewFeature/Lambda表达式$
这里需要注意的是，如果以传值方式捕获外部变量，则在Lambda表达式函数体中不能修改该外部变量的值。
*/
