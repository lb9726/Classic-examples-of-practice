#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int a, int b)
{
    return  a < b;
}

int main()
{
    vector<int> myvec{ 3, 2, 5, 7, 3, 2 };
    vector<int> lbvec(myvec);

    sort(myvec.begin(), myvec.end(), cmp); // 旧式做法
    cout << "predicate function:" << endl;
    for (int it : myvec)
        cout << it << ' ';
    cout << endl;

    sort(lbvec.begin(), lbvec.end(), [](int a, int b) -> bool { return a < b; });   // Lambda表达式
    cout << "lambda expression:" << endl;
    for (int it : lbvec)
        cout << it << ' ';
    cout << endl;
}
/*

libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_NewFeature/Lambda表达式$ g++ 001_example.cpp -o 001 -std=c++11
libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_NewFeature/Lambda表达式$ ./001 
predicate function:
2 2 3 3 5 7 
lambda expression:
2 2 3 3 5 7 
libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_NewFeature/Lambda表达式$ 

*/


