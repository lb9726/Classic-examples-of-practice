#include<iostream>
//using namespace std; // 使用这个时要定义成T min(T &x, T &y) 引用的才行
using std::cout;
using std::endl;
template <typename T>
T min(T x, T y)
{
    return (x<y) ? x : y;
}

int main()
{
    int n1 = 2, n2 = 10;
    double d1 = 1.5, d2 = 5.6;
    char a = 'a', b = 'b';
    cout << "较小整数:"<< min(n1, n2) << endl;
    cout << "较小实数:"<< min(d1, d2) << endl;
    cout << "较小字符:"<< min(a, b) << endl;
    return 0;
}
