#ifndef INVOKER_H
#define INVOKER_H

class Command;

class Invoker
{
public:
    Invoker(Command* cmd);
    ~Invoker();
    void invoke();
protected:
private:
    Command* _cmd;
};

#endif // INVOKER_H
