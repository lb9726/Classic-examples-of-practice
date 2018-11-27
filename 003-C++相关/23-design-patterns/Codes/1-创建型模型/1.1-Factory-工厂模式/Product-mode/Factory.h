#ifndef FACTORY_H
#define FACTORY_H
// #include "Product.h"    包含头文件时也可以编译通过并且运行
class Product;

class Factory
{
public:
    virtual ~Factory() = 0;
    virtual Product *CreateProduct() = 0;
protected:
    Factory();
private:
};

class ConcreateFactory:public Factory
{
public:
    ~ConcreateFactory();
    ConcreateFactory();
    Product* CreateProduct();
protected:
private:
};
#endif
