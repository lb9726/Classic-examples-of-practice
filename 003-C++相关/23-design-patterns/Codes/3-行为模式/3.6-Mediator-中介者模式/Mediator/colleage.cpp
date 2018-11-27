#include "colleage.h"
#include "mediator.h"
#include <iostream>
using namespace std;

Colleage::Colleage()
{
}

Colleage::Colleage(Mediator *mdt)
{
    this->_mdt = mdt;
}

Colleage::~Colleage()
{

}

ConcreteColleageA::ConcreteColleageA()
{

}

ConcreteColleageA::~ConcreteColleageA()
{

}

ConcreteColleageA::ConcreteColleageA(Mediator *mdt)
    :Colleage(mdt)
{

}

string ConcreteColleageA::getState()
{
    return _sdt;
}

void ConcreteColleageA::setState(const string &sdt)
{
    _sdt = sdt;
}

void ConcreteColleageA::action()
{
    _mdt->doActionFromAtoB();
    cout<<__FUNCTION__<<" State of ConcreteColleageA: "<<this->getState()<<endl;
}

ConcreteColleageB::ConcreteColleageB()
{

}

ConcreteColleageB::ConcreteColleageB(Mediator *mdt)
    :Colleage(mdt)
{

}

ConcreteColleageB::~ConcreteColleageB()
{

}

void ConcreteColleageB::action()
{
    _mdt->doActionFromBtoA();
    cout<<__FUNCTION__<<" State of ConcreteColleageB: "<<this->getState()<<endl;
}

void ConcreteColleageB::setState(const string &sdt)
{
    _sdt = sdt;
}

string ConcreteColleageB::getState()
{
    return _sdt;
}
