#include<iostream>
#include<memory>

using namespace std;

int main() 
{
    shared_ptr<string> pStr = make_shared<string>(10, 'a');
    cout << pStr.unique() << endl;  // true

    shared_ptr<string> pStr2(pStr);
    cout << pStr2.unique() << endl; // false;
}
/*
g++ 004_testUnique.cpp -o 004 -std=c++11
libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_智能指针$ ./004 
1
0

*/
