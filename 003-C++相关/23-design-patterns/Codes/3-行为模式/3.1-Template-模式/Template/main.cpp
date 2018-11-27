#include "template.h"

int main(int argc, char *argv[])
{
    AbstractClass *p1 = new ConcreteClass1();
    AbstractClass *p2 = new ConcreteClass2();

    p1->TemplateMethod(); // TemplateMethod 是父类的方法
    p2->TemplateMethod();

    return 0;
}
/*
代码说明
由于 Template 模式的实现代码很简单,因此解释是多余的。
其关键是将通用算法(逻辑)封装起来,而将算法细节让子类实现(多态)。
唯一注意的是我们将原语操作(细节算法)定义未保护(Protected)成员,只供模板方法调用(子类可以)。

Template 模式是很简单模式,但是也应用很广的模式。如上面的分析和实现中阐明的
Template 是采用继承的方式实现算法的异构,其关键点就是将通用算法封装在抽象基类中,
并将不同的算法细节放到子类中实现。
Template 模式获得一种反向控制结构效果,这也是面向对象系统的分析和设计中一个原则
DIP(依赖倒置:Dependency Inversion Principles)。
其含义就是父类调用子类的操作(高层模块调用低层模块的操作),低层模块实现高层模块声明的接口。
这样控制权在父类(高层模块),低层模块反而要依赖高层模块。

继承的强制性约束关系也让 Template 模式有不足的地方,我们可以看到对于
ConcreteClass 类中的实现的原语方法 PrimitiveOperation1(),是不能被别的类复用。
假设我们要创建一个 AbstractClass 的变体 AnotherAbstractClass,并且两者只是通用算法不一样,
其原语操作想复用 AbstractClass 的子类的实现。
但是这是不可能实现的,因为 ConcreteClass 继承自AbstractClass,也就继承了 AbstractClass 的通用算法,
AnotherAbstractClass 是复用不了ConcreteClass 的实现,因为后者不是继承自前者。
Template 模式暴露的问题也正是继承所固有的问题,Strategy 模式则通过组合(委托)
来达到和 Template 模式类似的效果,其代价就是空间和时间上的代价,关于 Strategy 模式的
详细讨论请参考 Strategy 模式解析。

*/
