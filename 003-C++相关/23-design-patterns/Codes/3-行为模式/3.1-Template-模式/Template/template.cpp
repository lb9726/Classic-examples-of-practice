#include "template.h"
#include <iostream>
using namespace std;

AbstractClass::AbstractClass()
{

}

AbstractClass::~AbstractClass()
{

}

void AbstractClass::TemplateMethod()
{
    cout <<__FUNCTION__<<endl;
    this->PrimitiveOperation1();
    this->PrimitiveOperation2();
}

ConcreteClass1::ConcreteClass1()
{

}

ConcreteClass1::~ConcreteClass1()
{

}

void ConcreteClass1::PrimitiveOperation1()
{
    cout<<"ConcreteClass1..."<<__FUNCTION__<<endl;
}

void ConcreteClass1::PrimitiveOperation2()
{
    cout<<"ConcreteClass1..."<<__FUNCTION__<<endl;
}

ConcreteClass2::ConcreteClass2()
{

}

ConcreteClass2::~ConcreteClass2()
{

}

void ConcreteClass2::PrimitiveOperation1()
{
    cout<<"ConcreteClass2..."<<__FUNCTION__<<endl;
}

void ConcreteClass2::PrimitiveOperation2()
{
    cout<<"ConcreteClass2..."<<__FUNCTION__<<endl;

}
