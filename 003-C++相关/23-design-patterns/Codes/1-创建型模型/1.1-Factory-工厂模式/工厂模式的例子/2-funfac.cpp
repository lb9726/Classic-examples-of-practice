/*
工厂方法模式
具体情形：最近莫名肥皂需求激增!！ 于是要独立每个生产线，每个生产线只生产一种肥皂。
UML图如下：

        其实这才是真正的工厂模式，简单工厂模式只能算是“坑爹版”的工厂模式。我们能很容易看出工厂方法模式和简单工厂模式的区别之处。工厂方法模式的应用并不是只是为了封装对象的创建，而是要把对象的创建放到子类中实现：Factory中只是提供了对象创建的接口，其实现将放在Factory的子类ConcreteFactory中进行。
对于工厂方法模式的组成：
1)抽象工厂角色： 这是工厂方法模式的核心，它与应用程序无关。是具体工厂角色必须实现的接口或者必须继承的父类。
2)具体工厂角色：它含有和具体业务逻辑有关的代码。由应用程序调用以创建对应的具体产品的对象。
3)抽象产品角色：它是具体产品继承的父类或者是实现的接口。
4)具体产品角色：具体工厂角色所创建的对象就是此角色的实例。
缺点：每增加一种产品，就需要增加一个对象的工厂。如果这家公司发展迅速，推出了很多新的处理器核，那么就要开设相应的新工厂。在C++实现中，就是要定义一个个的工厂类。显然，相比简单工厂模式，工厂方法模式需要更多的类定义。
代码实现：
*/

#include <iostream>  
using namespace std;  
enum SOAPTYPE {SFJ,XSL,NAS};  
  
class soapBase  
{  
    public:  
    virtual ~soapBase(){};  
    virtual void show() = 0;  
};  
  
class SFJSoap:public soapBase  
{  
    public:  
    void show() {cout<<"SFJ Soap!"<<endl;}  
};  
  
class XSLSoap:public soapBase  
{  
    public:  
    void show() {cout<<"XSL Soap!"<<endl;}  
};  
  
class NASSoap:public soapBase  
{  
    public:  
    void show() {cout<<"NAS Soap!"<<endl;}  
};  
  
class FactoryBase  
{  
    public:  
    virtual soapBase * creatSoap() = 0;  
};  
  
class SFJFactory:public FactoryBase  
{  
    public:  
    soapBase * creatSoap()  
    {  
        return new SFJSoap();  
    }  
};  
  
class XSLFactory:public FactoryBase  
{  
    public:  
    soapBase * creatSoap()  
    {  
        return new XSLSoap();  
    }  
};  
  
class NASFactory:public FactoryBase  
{  
    public:  
    soapBase * creatSoap()  
    {  
        return new NASSoap();  
    }  
};  
  
int main()  
{  
    SFJFactory factory1;  
    soapBase* pSoap1 = factory1.creatSoap();  
    pSoap1->show();  
    XSLFactory factory2;  
    soapBase* pSoap2 = factory2.creatSoap();  
    pSoap2->show();  
    NASFactory factory3;  
    soapBase* pSoap3 = factory3.creatSoap();  
    pSoap3->show();  
    delete pSoap1;  
    delete pSoap2;  
    delete pSoap3;  
    return 0;  
}  
/*
运行结果：
SFJ Soap!
XSL Soap!
NAS Soap!
*/


