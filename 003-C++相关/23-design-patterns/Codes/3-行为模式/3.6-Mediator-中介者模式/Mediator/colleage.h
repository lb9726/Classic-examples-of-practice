#ifndef COLLEAGE_H
#define COLLEAGE_H
#include <string>
using namespace std;

class Mediator;

class Colleage
{
public:
    virtual ~Colleage();
    virtual void action() = 0;
    virtual void setState(const string& sdt) = 0;
    virtual string getState() = 0;

protected:
    Colleage();
    Colleage(Mediator* mdt);
    Mediator* _mdt;
private:
};

class ConcreteColleageA:public Colleage
{
public:
    ConcreteColleageA();
    ConcreteColleageA(Mediator* mdt);
    ~ConcreteColleageA();
    void action();
    void setState(const string& sdt);
    string getState();

protected:
private:
    string _sdt;
};

class ConcreteColleageB:public Colleage
{
public:
    ConcreteColleageB();
    ConcreteColleageB(Mediator* mdt);
    ~ConcreteColleageB();
    void action();
    void setState(const string& sdt);
    string getState();
protected:
private:
    string _sdt;
};

#endif // COLLEAGE_H
