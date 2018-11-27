#include<iostream>
using namespace std; // 使用这个时要定义成T min(T &x, T &y) 引用的才行

template <class T>  //template <typename T> typename 和class 等价
T min(T x, T y)
{
    return (x<y) ? x : y;
}

int main()
{
    int n1 = 2, n2 = 10;
    double d1 = 1.5, d2 = 5.6;
    cout << "较小整数:"<< min(n1, n2) << endl;
    cout << "较小实数:"<< min(d1, d2) << endl;
    return 0;
}
/*
Mini_Max.cpp: In function ‘int main()’:
Mini_Max.cpp:14:41: error: call of overloaded ‘min(int&, int&)’ is ambiguous
Mini_Max.cpp:14:41: note: candidates are:
Mini_Max.cpp:5:3: note: T min(T, T) [with T = int]
/usr/include/c++/4.6/bits/stl_algobase.h:187:5: note: const _Tp& std::min(const _Tp&, const _Tp&) [with _Tp = int]
Mini_Max.cpp:15:41: error: call of overloaded ‘min(double&, double&)’ is ambiguous
Mini_Max.cpp:15:41: note: candidates are:
Mini_Max.cpp:5:3: note: T min(T, T) [with T = double]
/usr/include/c++/4.6/bits/stl_algobase.h:187:5: note: const _Tp& std::min(const _Tp&, const _Tp&) [with _Tp = double]
*/
