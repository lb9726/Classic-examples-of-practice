#include "memento.h"

Originator::Originator()
{
    _sdt = "";
    _mt = 0;
}

Originator::Originator(const Originator::State &sdt)
{
    _sdt = sdt;
    _mt = 0;
}

Originator::~Originator()
{

}

Memento *Originator::createMemento()
{
    return new Memento(_sdt);
}

Originator::State Originator::getState()
{
    return _sdt;
}

void Originator::setState(const Originator::State &sdt)
{
    _sdt = sdt;
}

void Originator::printState()
{
    cout << this->_sdt<<"...."<<__FUNCTION__<<endl; // #include <iostream>
}

void Originator::setMemento(Memento *men)
{

}

void Originator::restoreToMemento(Memento *mt)
{
    this->_sdt = mt->getState();
}

Memento::Memento()
{

}

Memento::Memento(const State &sdt)
{
    _sdt = sdt;
}

Memento::~Memento()
{

}

void Memento::setState(const State &sdt)
{
    _sdt = sdt;
}

Memento::State Memento::getState()
{
    return _sdt;
}
