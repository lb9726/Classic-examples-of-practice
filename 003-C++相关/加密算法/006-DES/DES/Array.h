#ifndef ARRAY_H
#define ARRAY_H

#include <string>

/***********************
 *数组类
 *为了更安全的操作
 *每次访问检查下标
 *更方便进行调试
 *尝试使用
**********************/


class Array
{
    public:
        ///构造函数
        Array();
        Array(int n);
        Array(int n, std::string s);
        Array(const Array &a);
        Array(const Array &a, std::string s);
        ~Array();

        ///获取信息
        int    get(int n) const;   //获取元素，用于const
        int    size() const;

        ///操作数组
        int&   operator[] (int n); //获取元素
        void   setName(std::string s);
        Array  operator =(const Array& arr);
        Array  sub(int b, int e) const;

    protected:
        int *a;
        int length;
        std::string name;  //保存名字，用于Debug

    protected:
        void set(int n);
        void set(const Array &a);
};





#endif // ARRAY_H
