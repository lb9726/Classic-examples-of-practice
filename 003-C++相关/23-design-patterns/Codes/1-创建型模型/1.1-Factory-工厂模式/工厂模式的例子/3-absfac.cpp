/*
抽象工厂模式
具体情形：这个肥皂厂发现搞牙膏也很赚钱，决定做牙膏。牙膏有高档低档，肥皂也是。现在搞两个厂房，一个生产低档的牙膏和肥皂，一个生产高档的牙膏和肥皂。
比如，厂房一生产中华牙膏、娜爱斯肥皂，厂房二生产黑人牙膏和舒肤佳牙膏
 UML图如下：

对于上面的结构图，可以看出抽象工厂模式，比前两者更为的复杂和一般性，抽象工厂模式和工厂方法模式的区别就在于需要创建对象的复杂程度上。
抽象工厂模式：给客户端提供一个接口，可以创建多个产品族中的产品对象 ，而且使用抽象工厂模式还要满足一下条件：
1)系统中有多个产品族，而系统一次只可能消费其中一族产品。
2)同属于同一个产品族的产品以其使用。
抽象工厂模式的组成（和工厂方法模式一样）：
1)抽象工厂角色：这是工厂方法模式的核心，它与应用程序无关。是具体工厂角色必须实现的接口或者必须继承的父类。
2)具体工厂角色：它含有和具体业务逻辑有关的代码。由应用程序调用以创建对应的具体产品的对象。
3)抽象产品角色：它是具体产品继承的父类或者是实现的接口。
4)具体产品角色：具体工厂角色所创建的对象就是此角色的实例。
代码实现
*/

#include <iostream>  
using namespace std;  
enum SOAPTYPE {SFJ,XSL,NAS};  
enum TOOTHTYPE {HR,ZH};  
  
class SoapBase  
{  
public:  
    virtual ~SoapBase(){}
    virtual void show() = 0;  
};  
  
class SFJSoap:public SoapBase  
{  
public:  
    void show() {cout<<"SFJ Soap!"<<endl;}  
};  
  
class NASSoap:public SoapBase  
{  
public:  
    void show() {cout<<"NAS Soap!"<<endl;}  
};  
  
class ToothBase  
{  
public:  
    virtual ~ToothBase(){}
    virtual void show() = 0;  
};  
  
class HRTooth:public ToothBase  
{  
public:  
    void show() {cout<<"Hei ren Toothpaste!"<<endl;}  
};  
  
class ChinaTooth:public ToothBase  
{  
public:  
    void show() {cout<<"China Toothpaste!"<<endl;}  
};  
  
class FactoryBase  
{  
public:  
    virtual SoapBase * creatSoap() = 0;  
    virtual ToothBase * creatToothpaste() = 0;  
};  
  
class FactoryA :public FactoryBase  
{  
public:  
    SoapBase * creatSoap()  
    {  
        return new SFJSoap();  
    }  
      
    ToothBase * creatToothpaste()  
    {  
        return new HRTooth();  
    }  
};  
  
class FactoryB :public FactoryBase  
{  
public:  
    SoapBase * creatSoap()  
    {  
        return new NASSoap();  
    }  
      
    ToothBase * creatToothpaste()  
    {  
        return new ChinaTooth();  
    }  
};  
  
  
int main()  
{  
    FactoryA factory1;  
    FactoryB factory2;  
    SoapBase *pSoap1 = NULL;  
    ToothBase *pToothpaste1 = NULL;  
    pSoap1 = factory1.creatSoap();  
    pToothpaste1 = factory1.creatToothpaste();  
    pSoap1->show();  
    pToothpaste1->show();  
      
    SoapBase *pSoap2 = NULL;  
    ToothBase *pToothpaste2 = NULL;  
    pSoap2 = factory2.creatSoap();  
    pToothpaste2 = factory2.creatToothpaste();  
    pSoap2->show();  
    pToothpaste2->show();  
      
    delete pSoap1;  
    delete pSoap2;  
    delete pToothpaste1;  
    delete pToothpaste2;  
      
    return 0;  
}  





