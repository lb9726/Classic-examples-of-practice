#include <iostream>
using namespace std;

int main()
{
    int a = 123;
    auto f = [a] { cout << a << endl; }; 
    f(); // 输出：123
}
/*

上面这个例子先声明了一个整型变量a，然后再创建Lambda表达式，该表达式“捕获”了a变量，这样在Lambda表达式函数体中就可以获得该变量的值。

类似参数传递方式（值传递、引入传递、指针传递），在Lambda表达式中，外部变量的捕获方式也有值捕获、引用捕获、隐式捕获。

libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_NewFeature/Lambda表达式$ g++ 002_example.cpp -o 002 -std=c++11
libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_NewFeature/Lambda表达式$ ./002
123
libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_NewFeature/Lambda表达式$
*/

