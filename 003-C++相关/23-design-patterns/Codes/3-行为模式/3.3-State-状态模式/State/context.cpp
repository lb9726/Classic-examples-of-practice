#include "context.h"
#include "state.h"
#include <stddef.h> // error: ‘NULL’ was not declared in this scope
#include <iostream>
using namespace std;

Context::Context()
{

}

Context::Context(State *state)
{
    this->_state = state;
}

Context::~Context()
{
    if (NULL != _state)
    {
        delete _state;
        _state = NULL;
        cout<<__FUNCTION__<<" is not null will delete"<<endl;
    }
}

void Context::OperationInterface()
{
    _state->OperationInterface(this);
}

bool Context::ChangeState(State *state)
{
    this->_state = state;
    return true;
}

void Context::OperationChangeState()
{
    _state->OperationChangeState(this);
}



