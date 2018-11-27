#include <iostream>
#include "command.h"
#include "invoker.h"
#include "reciever.h"
using namespace std;

int main(int argc, char *argv[])
{
    Reciever* rev = new Reciever();
    Command* cmd = new ConcreteCommand(rev);
    Invoker* inv = new Invoker(cmd);
    inv->invoke();
    return 0;
}

/*
问题
Command 模式通过将请求封装到一个对象(Command)中,并将请求的接受者存放到
具体的 ConcreteCommand 类中(Receiver)中,从而实现调用操作的对象和操作的具体实现
者之间的解耦。

模式选择
Command 模式结构图中,将请求的接收者(处理者)放到 Command 的具体子类
ConcreteCommand 中,当请求到来时(Invoker 发出 Invoke 消息激活 Command 对象),
ConcreteCommand 将处理请求交给 Receiver 对象进行处理。

代码说明
Command 模式在实现的实现和思想都很简单,其关键就是将一个请求封装到一个类中
(Command),再提供处理对象(Receiver),最后 Command 命令由 Invoker 激活。另外,我
们可以将请求接收者的处理抽象出来作为参数传给 Command 对象,实际也就是回调的机制
(Callback)来实现这一点,也就是说将处理操作方法地址(在对象内部)通过参数传递给
Command 对象,Command 对象在适当的时候(Invoke 激活的时候)再调用该函数。这里就
要用到 C++中的类成员函数指针的概念,为了方便学习,这里给出一个简单的实现源代码供
参考:

问题
Command 模式通过将请求封装到一个对象(Command)中,并将请求的接受者存放到
具体的 ConcreteCommand 类中(Receiver)中,从而实现调用操作的对象和操作的具体实现
者之间的解耦。

模式选择
Command 模式结构图中,将请求的接收者(处理者)放到 Command 的具体子类
ConcreteCommand 中,当请求到来时(Invoker 发出 Invoke 消息激活 Command 对象),
ConcreteCommand 将处理请求交给 Receiver 对象进行处理。

代码说明
Command 模式在实现的实现和思想都很简单,其关键就是将一个请求封装到一个类中
(Command),再提供处理对象(Receiver),最后 Command 命令由 Invoker 激活。另外,我
们可以将请求接收者的处理抽象出来作为参数传给 Command 对象,实际也就是回调的机制
(Callback)来实现这一点,也就是说将处理操作方法地址(在对象内部)通过参数传递给
Command 对象,Command 对象在适当的时候(Invoke 激活的时候)再调用该函数。这里就
要用到 C++中的类成员函数指针的概念,为了方便学习,这里给出一个简单的实现源代码供
参考:
*/
