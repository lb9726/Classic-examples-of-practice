#ifndef MEDIATOR_H
#define MEDIATOR_H

class Colleage;

class Mediator
{
public:
    virtual ~Mediator();
    virtual void doActionFromAtoB() = 0;
    virtual void doActionFromBtoA() = 0;

protected:
    Mediator();
private:
};

class ConcreteMediator:public Mediator
{
public:
    ConcreteMediator();
    ConcreteMediator(Colleage* clgA, Colleage* clgB);
    ~ConcreteMediator();
    void setConcreteColleageA(Colleage* clgA);
    void setConcreteColleageB(Colleage* clgB);
    Colleage* getConcreteColleageA();
    Colleage* getConcreteColleageB();
    void introColleage(Colleage* clgA, Colleage* clgB);
    void doActionFromAtoB();
    void doActionFromBtoA();

protected:
private:
    Colleage* _clgA;
    Colleage* _clgB;
};

#endif // MEDIATOR_H
