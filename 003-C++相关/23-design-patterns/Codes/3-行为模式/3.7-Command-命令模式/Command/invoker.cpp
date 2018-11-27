#include "invoker.h"
#include "command.h"
#include <iostream>

Invoker::Invoker(Command *cmd)
{
    _cmd = cmd;
}

Invoker::~Invoker()
{
    delete _cmd;
    _cmd = NULL;
}

void Invoker::invoke()
{
    _cmd->excute();
}
