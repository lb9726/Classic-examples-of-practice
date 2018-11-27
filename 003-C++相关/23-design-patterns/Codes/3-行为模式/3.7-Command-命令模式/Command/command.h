#ifndef COMMAND_H
#define COMMAND_H

class Reciever;

class Command
{
public:
    virtual ~Command();
    virtual void excute() = 0;
protected:
    Command();
private:
};

class ConcreteCommand:public Command
{
public:
    ConcreteCommand(Reciever* rev);
    ~ConcreteCommand();
    void excute();
protected:
private:
    Reciever* _rev;
};

#endif // COMMAND_H
