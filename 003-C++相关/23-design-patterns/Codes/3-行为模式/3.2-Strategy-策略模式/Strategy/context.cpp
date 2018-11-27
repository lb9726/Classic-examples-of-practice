#include "context.h"
#include "strategy.h"
#include <iostream>
using namespace std;

Context::Context(Strategy *stg)
{
    _stg = stg;
}

Context::~Context()
{
    if (NULL != _stg)
    {
        delete _stg;
        _stg = NULL;
        cout<<__FUNCTION__<<" is not null"<<endl;
    }
    else
    {
        cout<<__FUNCTION__<<" is null"<<endl;
    }
}

void Context::DoAction()
{
    _stg->AlgrithmInterface();
}
