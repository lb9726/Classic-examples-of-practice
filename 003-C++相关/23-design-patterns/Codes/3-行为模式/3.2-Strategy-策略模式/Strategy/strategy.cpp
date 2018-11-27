#include "strategy.h"
#include <iostream>
using namespace std;

Strategy::Strategy()
{

}

Strategy::~Strategy()
{
    cout<<__FUNCTION__<<"..."<<endl;
}

void Strategy::AlgrithmInterface()
{

}

ConcreteStrategyA::ConcreteStrategyA()
{

}

ConcreteStrategyA::~ConcreteStrategyA()
{
    cout<<__FUNCTION__<<"..."<<endl;
}

void ConcreteStrategyA::AlgrithmInterface()
{
    cout<<" test ConcreteStrategyA... "<<__FUNCTION__<<endl;
}

ConcreteStrategyB::ConcreteStrategyB()
{

}

ConcreteStrategyB::~ConcreteStrategyB()
{
    cout<<__FUNCTION__<<"..."<<endl;
}

void ConcreteStrategyB::AlgrithmInterface()
{
    cout<<"test ConcreteStrategyB..."<<__FUNCTION__<<endl;
}


