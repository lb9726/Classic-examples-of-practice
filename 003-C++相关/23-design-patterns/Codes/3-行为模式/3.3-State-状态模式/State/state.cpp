#include "state.h"
#include "context.h"
#include <iostream>
using namespace std;

State::State()
{

}

State::~State()
{

}

void State::OperationInterface(Context *con)
{
    cout<<"State::..."<<__FUNCTION__<<endl;
}

bool State::ChangeState(Context *con, State *st)
{
    con->ChangeState(st);
    return true;
}

void State::OperationChangeState(Context *con)
{

}

ConcreteStateA::ConcreteStateA()
{

}

ConcreteStateA::~ConcreteStateA()
{

}

void ConcreteStateA::OperationInterface(Context *con)
{
    cout<<"ConcreteStateA::"<<__FUNCTION__<<"......"<<endl;
}

void ConcreteStateA::OperationChangeState(Context *con)
{
    OperationInterface(con);
    this->ChangeState(con, new ConcreteStateB());
}

ConcreteStateB::ConcreteStateB()
{

}

ConcreteStateB::~ConcreteStateB()
{

}

void ConcreteStateB::OperationInterface(Context *con)
{
    cout<<"ConcreteStateB::"<<__FUNCTION__<<"...."<<endl;
}

void ConcreteStateB::OperationChangeState(Context *con)
{
    OperationInterface(con);
    this->ChangeState(con, new ConcreteStateA());
}
