#include<iostream>
using namespace std;

class Rect
{
public:
    Rect()                   // 构造函数，p指向堆中分配的一空间
    {
        p = new int(100);
    }
    
    Rect(const Rest &r)
    {
        width = r.width;
        height = r.height;
        p = new int;        // 为新对象重新动态分配空间
        *p = *(r.p);
    }
    
    ~Rect()                // 析构函数，释放动态分配的空间
    {
        if (NULL != p)
        {
            delete p;
        }
    }
    
private:
    int width ;
    int height;
    int *p;               // 指针成员
};





