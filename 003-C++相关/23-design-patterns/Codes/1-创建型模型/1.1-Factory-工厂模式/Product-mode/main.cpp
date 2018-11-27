#include "Factory.h"
#include "Product.h"
#include <iostream>
using namespace std;

int main()
{
    Factory* fac = new ConcreateFactory();
    Product* p = fac->CreateProduct();
    delete fac;
    delete p;
    return 0;
}

/*
 * 代码说明
示例代码中给出的是 Factory 模式解决父类中并不知道具体要实例化哪一个具体的子类
的问题,至于为创建对象提供接口问题,可以由 Factory 中附加相应的创建操作例如
Create***Product()即可。具体请参加讨论内容。
 讨论
Factory 模式在实际开发中应用非常广泛,面向对象的系统经常面临着对象创建问题:
要创建的类实在是太多了。而 Factory 提供的创建对象的接口封装(第一个功能),以及其
将类的实例化推迟到子类(第二个功能)都部分地解决了实际问题。一个简单的例子就是笔
者开开发 VisualCMCS 系统的语义分析过程中,由于要为文法中的每个非终结符构造一个类
处理,因此这个过程中对象的创建非常多,采用 Factory 模式后系统可读性性和维护都变得elegant 许多。

Factory 模式也带来至少以下两个问题:
1)如果为每一个具体的 ConcreteProduct 类的实例化提供一个函数体,那么我们可能不
得不在系统中添加了一个方法来处理这个新建的 ConcreteProduct,这样 Factory 的接口永远
就不可能封闭(Close)。当然我们可以通过创建一个 Factory 的子类来通过多态实现这一点,
但是这也是以新建一个类作为代价的。
2)在实现中我们可以通过参数化工厂方法,即给 FactoryMethod()传递一个参数用以
决定是创建具体哪一个具体的 Product(实际上笔者在 VisualCMCS 中也正是这样做的)。
当然也可以通过模板化避免 1)中的子类创建子类,其方法就是将具体 Product 类作为模板参
数,实现起来也很简单。
可以看出,Factory 模式对于对象的创建给予开发人员提供了很好的实现策略,但是
Factory 模式仅仅局限于一类类(就是说 Product 是一类,有一个共同的基类),如果我们要
为不同类的类提供一个对象创建的接口,那就要用 AbstractFactory 了。
 */
