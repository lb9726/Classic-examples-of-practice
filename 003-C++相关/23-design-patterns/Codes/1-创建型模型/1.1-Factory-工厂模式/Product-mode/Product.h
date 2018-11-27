#ifndef PRODUCT
#define PRODUCT

class Product
{
public:
    virtual ~Product() = 0;
protected:
    Product();    // 屏蔽构造函数
private:

};

class ConcreateProduct: public Product
{
public:
    ~ConcreateProduct();
    ConcreateProduct();
protected:

private:
};

#endif // PRODUCT

/* 我们把简单工厂方法归类到工厂方法中。
 * 工厂方法的目的是用来解决具有同一接口（基类）派生类对象的生成问题。
 * 尽管可以通过类的构造函数生成对象，但是，如果派生类的数量很大——即使几十个不同的派生类——对于程序设计而言也是困难的。
 * 这里有两个困难：其一是可读性，在一个程序里使用一个switch-case block判断具体的生成类型，程序几乎不能读，也增加了编码的难度；
 * 其二是扩展性，如果增加了新的派生类，就需要修改switch-case block。
 *
 * 解决上面问题的方法是把对象实体和生成分开：把“生成”定义成一个类。
 * 对于简单工厂方法，把用于生产每个对象的函数定义为一个类的函数；
 * 对于工厂方法，把“生成”每个对象的方法定义为一个类：派生自一个工厂接口类。
 * 每个“生成”函数都返回派生类的接口指针。
 * 从此可以看出，简单工厂方法其实没有增加程序的可读性和扩展性。
 * 对于工厂方法，可以在实际使用前把所有的生成类构造到一个序列里，
 * 然后把所有对象编号，每个编号是其生成类在序列的位置。
 * 这样就避免了使用switch-case block。
*/
