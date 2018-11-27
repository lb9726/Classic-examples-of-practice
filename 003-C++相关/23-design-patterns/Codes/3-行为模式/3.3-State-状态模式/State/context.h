#ifndef CONTEXT_H
#define CONTEXT_H

class State;
class Context
{
public:
    Context();
    Context(State* state);
    ~Context();
    void OperationInterface();
    void OperationChangeState();
protected:
private:
    friend class State; // //表明在 State 类中可以访问 Context 类的 private protected 字段
    bool ChangeState(State* state);
private:
    State* _state;
};

#endif // CONTEXT_H
