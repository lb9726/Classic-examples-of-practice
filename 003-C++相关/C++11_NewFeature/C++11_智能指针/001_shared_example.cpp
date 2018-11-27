#include <iostream>
#include <memory>
using  namespace std;

class Example
{
public:
    Example() : e(1) { cout << "Example Constructor..." << endl; }
    ~Example() { cout << "Example Destructor..." << endl; }

    int e;
};

int main() {

    shared_ptr<Example> pInt(new Example());
    cout << (*pInt).e << endl;
    cout << "pInt引用计数: " << pInt.use_count() << endl;

    shared_ptr<Example> pInt2 = pInt;
    cout << "pInt引用计数: " << pInt.use_count() << endl;
    cout << "pInt2引用计数: " << pInt2.use_count() << endl;
}
/*
g++ shared_example.cpp -o e -std=c++11
./e
Example Constructor...
1
pInt引用计数: 1
pInt引用计数: 2
pInt2引用计数: 2
Example Destructor...

libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_智能指针$ valgrind --tool=memcheck ./e
==12351== Memcheck, a memory error detector
==12351== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==12351== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==12351== Command: ./e
==12351== 
Example Constructor...
1
pInt引用计数: 1
pInt引用计数: 2
pInt2引用计数: 2
Example Destructor...
==12351== 
==12351== HEAP SUMMARY:
==12351==     in use at exit: 0 bytes in 0 blocks
==12351==   total heap usage: 2 allocs, 2 frees, 28 bytes allocated
==12351== 
==12351== All heap blocks were freed -- no leaks are possible
==12351== 
==12351== For counts of detected and suppressed errors, rerun with: -v
==12351== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


*/



