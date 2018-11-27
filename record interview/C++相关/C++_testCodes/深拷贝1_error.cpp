#include <iostream>
using namespace std;

class Rect
{
public:
    Rect()                   // 构造函数，p指向堆中分配的一空间
    {
        p = new int(100);
    }
    ~Rect()                 // 析构函数，释放动态分配的空间
    {
        if (NULL != p)
        {
            delete p;
        }
    }
    
private:
    int width;
    int height;
    int *p;                //指针成员
};

int main()
{
    Rect rect1;
    Rect rect2(rect1);     //复制对象
    return 0;
}
/*
*** Error in `./serror': double free or corruption (fasttop): 0x0000000000b61010 ***
已放弃 (核心已转储)

*/
