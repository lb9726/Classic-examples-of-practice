#ifndef MEMENTO_H
#define MEMENTO_H
#include <string>
#include <iostream>  //error: ‘cout’ was not declared in this scope
using namespace std;

class Memento;

class Originator
{
public:
    typedef string State;
    Originator();
    Originator(const State& sdt);
    ~Originator();
    Memento* createMemento();
    void setMemento(Memento* men);
    void restoreToMemento(Memento* mt);
    State getState();
    void setState(const State& sdt);
    void printState();

protected:
private:
    State _sdt;
    Memento* _mt;
};

class Memento
{
public:
protected:
private:
    // 这是最关键的地方,将 Originator 为 friend 类,可以访问内部信息,但是其他类不能访问
    friend class Originator;
    typedef string State;
    Memento();
    Memento(const State& sdt);
    ~Memento();
    void setState(const State& sdt);
    State getState();

private:
    State _sdt;
};

#endif // MEMENTO_H
