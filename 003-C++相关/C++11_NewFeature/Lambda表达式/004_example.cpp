#include <iostream>
#include <functional>
using namespace std;

void print_num(int x)
{
    cout<<"x = "<< x << endl;
}

int main()
{
    int m = [](int x) {return [](int y) { return y*2;}(x)+6;}(5);
    std::cout << "m: " << m << std::endl; // 输出m:16
    std::cout << "n: " << [](int x, int y) { return x + y; }(5, 4)<<std::endl; //输出n:9

    auto gFunc = [](int x) -> function<int(int)> { return [=](int y) { return x + y; }; };
    auto lFunc = gFunc(4);
    std::cout << lFunc(5) << std::endl;

    auto hFunc = [](const function<int(int)>& f, int z) { return f(z) + 1; };
    auto lb = hFunc(gFunc(7), 8);
    std::cout << "lb = " << lb << std::endl;

    int a = 111, b = 222;
    auto func = [=, &b]()mutable { a = 22; b = 333; std::cout << "a:" << a << " b:" << b << std::endl; };

    func();
    std::cout << "a:" << a << " b:" << b << std::endl;

    a = 333;
    auto func2 = [=, &a] { a = 444; std::cout << "a = " << a << " b = " << b << std::endl; };
    func2();

    auto func3 = [](int x) ->function<int(int)> { return [=](int y) { return x + y; }; };

    func3(5);

    std::function<void(int x)> f_display_42 = [](int x) { print_num(x); };
    f_display_42(44);
}
/*
g++ 004_example.cpp -o 004 -std=c++11

m: 16
n: 9
9
lb = 16
a:22 b:333
a:111 b:333
a = 444 b = 333
x = 44

*/

