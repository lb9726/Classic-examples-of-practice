#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
 
struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    // 注意：此处非虚析构函数 OK
    ~Base() { std::cout << "  Base::~Base()\n"; }
};
 
struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};
 
void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // 线程安全，虽然自增共享的 use_count
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread:\n"
                  << "  lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}
 
int main()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();
 
    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    std::thread t1(thr, p), t2(thr, p), t3(thr, p);
    p.reset(); // 从 main 释放所有权
    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    t1.join(); t2.join(); t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";
}
/*
使用以下命令进行编译，g++ shared_ptr.cpp -o shared_pt 会报错
/usr/include/c++/4.8/bits/c++0x_warning.h:32:2: error: #error This file requires compiler and library support for the ISO C++ 2011 standard. This support is currently experimental, and must be enabled with the -std=c++11 or -std=gnu++11 compiler options.

所以加上 -std=c++11  g++ shared_ptr.cpp -o shared_pt -std=c++11
但是运行的时候还是会报core dumped 核心已转储  

terminate called after throwing an instance of 'std::system_error'
  what():  Enable multithreading to use std::thread: Operation not permitted
Aborted (core dumped)  百度后推荐加上pthread 再次编译，运行通过了

g++ shared_ptr.cpp -o shared_pt -std=c++11 -lpthread 

libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_智能指针$ ./shared_pt
  Base::Base()
  Derived::Derived()
Created a shared Derived (as a pointer to Base)
  p.get() = 0x21be028, p.use_count() = 1
Shared ownership between 3 threads and released
ownership from main:
  p.get() = 0, p.use_count() = 0
local pointer in a thread:
  lp.get() = 0x21be028, lp.use_count() = 4
local pointer in a thread:
  lp.get() = 0x21be028, lp.use_count() = 3
local pointer in a thread:
  lp.get() = 0x21be028, lp.use_count() = 2
  Derived::~Derived()
  Base::~Base()
All threads completed, the last one deleted Derived


libo@ubuntu:~/Desktop/Repository/Classic-examples-of-practice/C++相关/C++11_智能指针$ valgrind --tool=memcheck ./shared_pt
==12059== Memcheck, a memory error detector
==12059== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==12059== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==12059== Command: ./shared_pt
==12059== 
  Base::Base()
  Derived::Derived()
Created a shared Derived (as a pointer to Base)
  p.get() = 0x5c3e058, p.use_count() = 1
Shared ownership between 3 threads and released
ownership from main:
  p.get() = 0, p.use_count() = 0
local pointer in a thread:
  lp.get() = 0x5c3e058, lp.use_count() = 4
local pointer in a thread:
  lp.get() = 0x5c3e058, lp.use_count() = 6
local pointer in a thread:
  lp.get() = 0x5c3e058, lp.use_count() = 2
  Derived::~Derived()
  Base::~Base()
All threads completed, the last one deleted Derived
==12059== 
==12059== HEAP SUMMARY:
==12059==     in use at exit: 0 bytes in 0 blocks
==12059==   total heap usage: 7 allocs, 7 frees, 1,112 bytes allocated
==12059== 
==12059== All heap blocks were freed -- no leaks are possible
==12059== 
==12059== For counts of detected and suppressed errors, rerun with: -v
==12059== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


*/



