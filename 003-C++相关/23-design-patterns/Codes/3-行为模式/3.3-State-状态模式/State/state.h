#ifndef STATE_H
#define STATE_H

class Context; //前置声明

class State
{
public:
    State();
    virtual ~State();
    virtual void OperationInterface(Context* con) = 0;
    virtual void OperationChangeState(Context* con) = 0;

protected:
    bool ChangeState(Context* con, State* st);
private:
    // bool ChangeState(Context* con, State* st);
};

class ConcreteStateA:public State
{
public:
    ConcreteStateA();
    virtual ~ConcreteStateA();
    virtual void OperationInterface(Context* con);
    virtual void OperationChangeState(Context* con);
protected:
private:
};

class ConcreteStateB: public State
{
public:
    ConcreteStateB();
    virtual ~ConcreteStateB();
    virtual void OperationInterface(Context* con);
    virtual void OperationChangeState(Context* con);
protected:
private:
};

#endif // STATE_H
