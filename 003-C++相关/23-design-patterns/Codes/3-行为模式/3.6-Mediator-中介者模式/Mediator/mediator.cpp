#include "mediator.h"
#include "colleage.h"

Mediator::Mediator()
{

}

Mediator::~Mediator()
{

}

ConcreteMediator::ConcreteMediator()
{

}

ConcreteMediator::ConcreteMediator(Colleage *clgA, Colleage *clgB)
{
    this->_clgA = clgA;
    this->_clgB = clgB;
}

ConcreteMediator::~ConcreteMediator()
{

}

void ConcreteMediator::setConcreteColleageA(Colleage *clgA)
{
    this->_clgA = clgA;
}

void ConcreteMediator::setConcreteColleageB(Colleage *clgB)
{
    this->_clgB = clgB;
}

Colleage *ConcreteMediator::getConcreteColleageA()
{
    return _clgA;
}

Colleage *ConcreteMediator::getConcreteColleageB()
{
    return _clgB;
}

void ConcreteMediator::introColleage(Colleage *clgA, Colleage *clgB)
{
    this->_clgA = clgA;
    this->_clgB = clgB;
}

void ConcreteMediator::doActionFromAtoB()
{
    _clgB->setState(_clgA->getState());
}

void ConcreteMediator::doActionFromBtoA()
{
    _clgA->setState(_clgB->getState());
}
