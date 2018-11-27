#include "subject.h"
#include "observer.h"

Subject::Subject()
{
    //****在模板的使用之前一定要 new,创建
    _obvs = new list<Observer*>;
}

Subject::~Subject()
{
    if (NULL != _obvs)
    {
        delete _obvs;
        _obvs = NULL;
        cout<<__FUNCTION__<<" _obvs is not null"<<endl;

    }
    else
    {
        cout<<__FUNCTION__<<" _obvs is null"<<endl;
    }
}

void Subject::Attach(Observer *obv)
{
    _obvs->push_front(obv);
}

void Subject::Detach(Observer *obv)
{
    if (NULL != obv)
    {
        _obvs->remove(obv);
    }
}

void Subject::Notify()
{
    list<Observer*>::iterator it;
    if (NULL != _obvs)
    {
        it = _obvs->begin();
        for(; it != _obvs->end(); ++it)
        {
            //关于模板和 iterator 的用法
            (*it)->Update(this);
        }
    }
}

// 纯虚函数在子类中必须实现
/*
 * 对于一般的虚函数，其实现是作为派生类的默认实现，即若派生类没有override基类中实现，则默认调用
基类中函数体；
但是如果在父类中实现了纯虚函数（接口）的函数体，则此时对于派生类意味着：
在父类中实现了接口的函数体，如果需要使用，请显式地调用。
 */

//State Subject::GetState()
//{

//}

//void Subject::SetState(const State &st)
//{

//}



ConcreteSubject::ConcreteSubject()
{
    _st = '\0';
}

ConcreteSubject::~ConcreteSubject()
{

}

State ConcreteSubject::GetState()
{
    return _st;
}

void ConcreteSubject::SetState(const State &st)
{
    _st = st;
}
