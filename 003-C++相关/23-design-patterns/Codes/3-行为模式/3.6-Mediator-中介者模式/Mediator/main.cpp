#include <iostream>
#include "mediator.h"
#include "colleage.h"
using namespace std;

int main(int argc, char *argv[])
{
    ConcreteMediator* m = new ConcreteMediator();
    ConcreteColleageA* c1 = new ConcreteColleageA(m);
    ConcreteColleageB* c2 = new ConcreteColleageB(m);

    m->introColleage(c1, c2);

    c1->setState("old");
    c2->setState("old");
    c1->action();
    c2->action();
    cout<< endl;

    c1->setState("new");
    c1->action();
    c2->action();
    cout<<endl;

    c2->setState("old");
    c2->action();
    c1->action();

    delete m;
    delete c1;
    delete c2;
    return 0;
}


/*
设计模式之中介者模式（Mediator）
问题
在面向对象系统的设计和开发过程中,对象之间的交互和通信是最为常见的情况,
因为对象间的交互本身就是一种通信。在系统比较小的时候,可能对象间的通信不是很多、对象
也比较少,我们可以直接硬编码到各个对象的方法中。
但是当系统规模变大,对象的量变引起系统复杂度的急剧增加,对象间的通信也变得越来越复杂,
这时候我们就要提供一个专门处理对象间交互和通信的类,这个中介者就是 Mediator 模式。
Mediator 模式提供将对象间的交互和通讯封装在一个类中,各个对象间的通信不必显势去声明和引用,
大大降低了系统的复杂性能(了解一个对象总比深入熟悉 n 个对象要好)。
另外 Mediator 模式还带来了系统对象间的松耦合,这些将在讨论中详细给出。

模式选择
Mediator 模式典型的结构图为:

Mediator 模式中,每个 Colleague 维护一个 Mediator,当要进行交互,例如图中
ConcreteColleagueA 和 ConcreteColleagueB 之间的交互就可以通过 ConcreteMediator 提供的
DoActionFromAtoB 来处理, ConcreteColleagueA 和 ConcreteColleagueB 不必维护对各自的引用,
甚至它们也不知道各个的存在。Mediator 通过这种方式将多对多的通信简化为了一(Mediator)对多(Colleague)的通信。

代码说明
Mediator 模式的实现关键就是将对象 Colleague 之间的通信封装到一个类种单独处理,
为了模拟 Mediator 模式的功能,这里给每个 Colleague 对象一个 string 型别以记录其状态,
并通过状态改变来演示对象之间的交互和通信。这里主要就 Mediator 的示例运行结果给出
分析:
(1)将 ConcreteColleageA 对象设置状态“old”,ConcreteColleageB 也设置状态“old”;
(2)ConcreteColleageA 对象改变状态,并在 Action 中和 ConcreteColleageB 对象进行通信,
并改变ConcreteColleageB 对象的状态为“new”;
(3)ConcreteColleageB 对象改变状态,并在 Action 中和 ConcreteColleageA 对象进行通信,
并改变ConcreteColleageA 对象的状态为“new”;
注意到,两个 Colleague 对象并不知道它交互的对象,并且也不是显示地处理交互过程,
这一切都是通过 Mediator 对象完成的,示例程序运行的结果也正是证明了这一点。

讨论
Mediator 模式是一种很有用并且很常用的模式,它通过将对象间的通信封装到一个类中,
将多对多的通信转化为一对多的通信,降低了系统的复杂性。Mediator 还获得系统解耦的特性,
通过 Mediator,各个 Colleague 就不必维护各自通信的对象和通信协议,
降低了系统的耦合性,Mediator 和各个 Colleague 就可以相互独立地修改了。
Mediator 模式还有一个很显著额特点就是将控制集中,集中的优点就是便于管理,也正
式符合了 OO 设计中的每个类的职责要单一和集中的原则。

*/
