#include "observer.h"
using namespace std;
Observer::Observer()
{
    _st = '\0';
}

Observer::~Observer()
{

}

ConcreteObserverA::ConcreteObserverA(Subject *sub)
{
    _sub = sub;
    _sub->Attach(this);
    // 观察者观察的是subject
    // ConcreteObserverA 并且为subject生成一张观察者的list，用于改变的时候去Notify
}

ConcreteObserverA::~ConcreteObserverA()
{// 在 ~ConcreteObserverA() 中只需要delete一次即可，在 ~ConcreteObserverB() 中可以不delete，因为是同一个变量
    if (NULL != _sub)
    {
        _sub->Detach(this);
        cout<<__FUNCTION__<<" _sub is not null will delete"<<endl;
        delete _sub;
        _sub = NULL;
    }
    else
    {
        cout<<__FUNCTION__<<" _sub is null"<<endl;
    }
}


Subject *ConcreteObserverA::GetSubject()
{
    return _sub;
}

void ConcreteObserverA::PrintInfo()
{
    cout<<__FUNCTION__<<"..."<< _sub->GetState()<<endl;
}

void ConcreteObserverA::Update(Subject *sub)
{
    _st = sub->GetState();
    PrintInfo();
}


ConcreteObserverB::ConcreteObserverB(Subject *sub)
{
    _sub = sub;
    _sub->Attach(this);
    // 观察者观察的是subject
    // ConcreteObserverB 并且为subject生成一张观察者的list，用于改变的时候去Notify
}

ConcreteObserverB::~ConcreteObserverB()
{
//    if (NULL != _sub)
//    {
//        _sub->Detach(this);
//        cout<<__FUNCTION__<<" _sub is not null"<<endl;
//        delete _sub;
//        _sub = NULL;
//    }
//    else
//    {
//        cout<<__FUNCTION__<<"_sub is null"<<endl;
//    }
    cout<<__FUNCTION__<<" is called"<<endl;
}

Subject *ConcreteObserverB::GetSubject()
{
    return _sub;
}

void ConcreteObserverB::PrintInfo()
{
    cout<<__FUNCTION__<<"..."<<_sub->GetState()<< endl;
}

void ConcreteObserverB::Update(Subject *sub)
{
    _st = sub->GetState();
    PrintInfo();
}
