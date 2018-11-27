#include <iostream>
using namespace std;

class Rect
{
public:
    Rect()  //构造函数，计数加一
    {
        count++;
    }
    
    ~Rect() // 析构函数，计数器减一
    {
        count--;
        cout<< count << endl;
    }
    
    static int getCount()  // 返回计数器的值
    {
        return count;
    }
    
private:
    int width;
    int height;
    static int count;  // 静态成员作为计数器    
};

int Rect::count = 0; // 初始化计数器

int main()
{
    Rect rect1;
    cout<< "The count of Rect:" << Rect::getCount() << endl;
    
    Rect rect2(rect1); // 使用rect1复制rect2，此时应该有两个对象
    cout << "The count of Rect:" << Rect::getCount() << endl;
    return 0;
    
}
