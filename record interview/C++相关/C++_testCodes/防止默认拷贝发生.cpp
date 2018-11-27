#include <iostream>
using namespace std;

//防止按值传递
class CExample
{
private:
    int a;
public:
    CExample(int b)
    {
        a = b;
        cout << "Creat:" << a << endl;
    }
private:
    //拷贝构造，只是声明
    CExample(const CExample &C);
public:
    ~CExample()
    {
        cout << "delete:"<< a << endl;
    }
    void show()
    {
        cout << a << endl;
    }
};

// 全局函数
void g_Fun(CExample C)
{
    cout << "test" << endl;
}

int main()
{
    CExample test(1);
    
    g_Fun(test); //按值传递将出错
    
    return 0;
}

/*
防止默认拷贝发生.cpp: In function ‘int main()’:
防止默认拷贝发生.cpp:17:5: error: ‘CExample::CExample(const CExample&)’ is private
防止默认拷贝发生.cpp:39:15: error: within this context
防止默认拷贝发生.cpp:30:6: error:   initializing argument 1 of ‘void g_Fun(CExample)’
*/












