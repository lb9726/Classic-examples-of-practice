#include<iostream>
#include<memory>
using namespace std;

class Example
{
public:
    Example(string n) : name(n) { cout << n << " constructor..." << endl; }
    ~Example() { cout << name << " destructor..." << endl; }

    string name;
};

int main() {

    shared_ptr<Example> pStr = make_shared<Example>("a object");
    shared_ptr<Example> pStr2 = make_shared<Example>("b object");
    cout << pStr.use_count() << endl;
    cout << pStr2.use_count() << endl;

    pStr = pStr2;   // 此后pStr和pStr指向相同对象
    cout << pStr->name << endl;
    cout << pStr2->name << endl;
}

/*
g++ 003_example.cpp -o e -std=c++11
libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_智能指针$ ./e
a object constructor...
b object constructor...
1
1
a object destructor...
b object
b object
b object destructor...

libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_智能指针$ valgrind --tool=memcheck ./e
==12540== Memcheck, a memory error detector
==12540== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==12540== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==12540== Command: ./e
==12540== 
a object constructor...
b object constructor...
1
1
a object destructor...
b object
b object
b object destructor...
==12540== 
==12540== HEAP SUMMARY:
==12540==     in use at exit: 0 bytes in 0 blocks
==12540==   total heap usage: 4 allocs, 4 frees, 130 bytes allocated
==12540== 
==12540== All heap blocks were freed -- no leaks are possible
==12540== 
==12540== For counts of detected and suppressed errors, rerun with: -v
==12540== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


*/
