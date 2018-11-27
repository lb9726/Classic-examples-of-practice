#include<iostream>
#include<string>
using namespace std;

class A
{
private:
    int num;
    string name;
public:
    void setNum(int n)
    {
        num = n;
        cout << "num = "<< num << endl;
    }
    void setName(string n)
    {
        name = n;
        cout << "name = "<< name << endl;
    }
    int getNum()
    {
        cout << "num = "<< num << endl;
        return num;
    }
    string getName()
    {
        cout << "name = "<< name << endl;
        return name;
    }
};

int main()
{
    A *a = new A();
    A *b = new A();
    a->setNum(5);
    a->setName("libo");
    
    b->setNum(6);
    b->setName("lihua");
    
    a->getNum();
    a->getName();
    return 0;
}

/*
每个对象对应的name，num变量都会维持自己对象所设置的内容不变，不是共享的内容
不会因为其中一个对象改变了一个值，另外一个对象的值也跟着改变
*/
