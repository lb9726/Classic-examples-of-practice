#include "command.h"
#include "reciever.h"
#include <iostream>
using namespace std;

Command::Command()
{

}

Command::~Command()
{

}

void Command::excute()
{

}

ConcreteCommand::ConcreteCommand(Reciever *rev)
{
    this->_rev = rev;
}

ConcreteCommand::~ConcreteCommand()
{
    delete this->_rev;
}

void ConcreteCommand::excute()
{
    _rev->action();
    cout<<"ConcreteCommand::"<<__FUNCTION__<<endl;
}
