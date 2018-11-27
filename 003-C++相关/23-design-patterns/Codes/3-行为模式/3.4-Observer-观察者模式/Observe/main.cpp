#include <iostream>
#include "subject.h"
#include "observer.h"

int main(int argc, char *argv[])
{
    ConcreteSubject* sub = new ConcreteSubject();
    Observer* o1 = new ConcreteObserverA(sub);
    Observer* o2 = new ConcreteObserverB(sub);
    sub->SetState("old");
    sub->Notify();
    sub->SetState("new"); // 也可以由 Observer 调用
    sub->Notify();

    delete o1;  // 会delete掉对应的sub //    delete sub;
    delete o2;

    return 0;
}

/*
代码说明
在 Observer 模式的实现中,Subject 维护一个 list 作为存储其所有观察者的容器。每当
调用 Notify 操作就遍历 list 中的 Observer 对象,并广播通知改变状态(调用 Observer 的 Update
操作)。目标的状态 state 可以由 Subject 自己改变(示例),也可以由 Observer 的某个操作引
起 state 的改变(可调用 Subject 的 SetState 操作)。Notify 操作可以由 Subject 目标主动广播
(示例),也可以由 Observer 观察者来调用(因为 Observer 维护一个指向 Subject 的指针)。
运行示例程序,可以看到当 Subject 处于状态“old”时候,依赖于它的两个观察者都显
示“old”,当目标状态改变为“new”的时候,依赖于它的两个观察者也都改变为“new”。

libo@ubuntu:~/Observe$ valgrind --tool=memcheck ./obv
==17937== Memcheck, a memory error detector
==17937== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==17937== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
==17937== Command: ./obv
==17937==
PrintInfo...old
PrintInfo...old
PrintInfo...new
PrintInfo...new
~ConcreteObserverA _sub is not null will delete
~Subject delete is called
~ConcreteObserverB is called
==17937==
==17937== HEAP SUMMARY:
==17937==     in use at exit: 0 bytes in 0 blocks
==17937==   total heap usage: 11 allocs, 11 frees, 270 bytes allocated
==17937==
==17937== All heap blocks were freed -- no leaks are possible
==17937==
==17937== For counts of detected and suppressed errors, rerun with: -v
==17937== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

*/
