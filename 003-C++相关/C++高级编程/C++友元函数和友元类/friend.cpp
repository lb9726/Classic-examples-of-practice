#include <math.h>
#include <iostream>
using namespace std;

class Point
{
public:
    Point(double xx, double yy)
    {
        x = xx;
        y = yy;
    }
    void Getxy();
    friend double Distance(Point &a, Point &b);// 类Point的友元函数
    friend class You;                          // 类Point的友元类
private:
    double x, y;
};


class You
{
public:
    double Multi(Point &a)
    {
        cout<<"a.x = "<<a.x<<"a.y = "<<a.y;
        return a.x * a.y + 1;
    }
};

void Point::Getxy()
{
    cout<<" ("<<x<<","<<y<<")"<<endl;
}

/*
 * 类Point的友元函数
 * 可以在类的外部使用类的对象，来引用x，y这两个private的私有变量
*/
double Distance(Point &a, Point &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main(void)
{
    Point p1(3.0, 4.0);
    Point p2(6.0, 8.0);
    p1.Getxy();
    p2.Getxy();

    // Distance是类Point的友元函数，不是成员函数
    double d = Distance(p1, p2);
    cout<<" Distance is "<<d<<endl;
    You you; /*友元类定义*/
    d = you.Multi(p1);
    cout<<" Math.Multi is "<<d<<endl;
    return 0;
}

