//http://blog.csdn.net/silangquan/article/details/20492293
/*
引出工厂模式的设计问题
◆ 1.为了提高内聚（Cohesion）和松耦合（Coupling），我们经常会抽象出一些类的公共接口以形成抽象基类或者接口。这样我们可以通过声明一个指向基类的指针来指向实际的子类实现，达到了多态的目的。这里很容易出现的一个问题 n 多的子类继承自抽象基类，我们不得不在每次要用到子类的地方就编写诸如 new ×××;的代码。这里带来两个问题：
客户程序员必须知道实际子类的名称（当系统复杂后，命名将是一个很不好处理的问题，为了处理可能的名字冲突，有的命名可能并不是具有很好的可读性和可记忆性，就姑且不论不同程序员千奇百怪的个人偏好了）。
程序的扩展性和维护变得越来越困难。
◆ 2.还有一种情况就是在父类中并不知道具体要实例化哪一个具体的子类。这里的意思为：假设我们在类 A 中要使用到类 B，B 是一个抽象父类，在 A 中并不知道具体要实例化那一个 B 的子类，但是在类 A 的子类 D 中是可以知道的。在 A 中我们没有办法直接使用类似于 new ×××的语句，因为根本就不知道×××是什么。

以上两个问题也就引出了工厂模式的两个最重要的功能：
定义创建对象的接口，封装了对象的创建；
使得具体化类的工作延迟到了子类中。
对于工厂模式，为了使其能更好的解决多种情况的问题，将其分为三类：简单工厂模式（Simple Factory），工厂方法模式（Factory Method），抽象工厂模式（Abstract Factory）。下面来一一搞定。


简单工厂
        具体情形：有一个肥皂厂，生产各种肥皂，有舒肤佳，夏士莲，娜爱斯等。给这个肥皂厂建模。
        UML图如下：

对于简单设计模式的结构图，我们可以很清晰的看到它的组成：
1) 工厂类角色：这是本模式的核心，含有一定的商业逻辑和判断逻辑。
2) 抽象产品角色：它一般是具体产品继承的父类或者实现的接口。
3) 具体产品角色：工厂类所创建的对象就是此角色的实例。
简单设计模式存在的目的很简单：定义一个用于创建对象的接口。
缺点：对修改不封闭，新增加产品您要修改工厂。违法了鼎鼎大名的开闭法则（OCP）。
代码实现：
*/


#include <iostream>  
using namespace std;  
enum PRODUCTTYPE {SFJ,XSL,NAS};  
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
  
class Factory  
{  
    public:  
    soapBase * creatSoap(PRODUCTTYPE type)  
    {  
        switch(type)  
        {  
            case SFJ:   
                return new SFJSoap();  
                break;  
            case XSL:  
                return new XSLSoap();  
                break;  
            case NAS:  
                return new NASSoap();  
                break;  
            default:break;  
        }  
          
    }  
};  
  
int main()  
{  
    Factory factory;  
    soapBase* pSoap1 = factory.creatSoap(SFJ);  
    pSoap1->show();  
    soapBase* pSoap2 = factory.creatSoap(XSL);  
    pSoap2->show();  
    soapBase* pSoap3 = factory.creatSoap(NAS);  
    pSoap3->show();  
    delete pSoap1;  
    delete pSoap2;  
    delete pSoap3;  
    return 0;  
}  
