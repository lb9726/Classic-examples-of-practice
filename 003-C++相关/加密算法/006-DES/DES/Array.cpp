#include "Array.h"


/***************************************
 *构造函数

***************************************/
Array::Array()
{
    a = NULL;
    length = 0;
}

Array::Array(int n)
{
    set(n);
    name = "N";
}

Array::Array(int n, std::string s)
{
    set(n);
    name = s;
}

Array::Array(const Array &arr)
{
    set(arr);
    name = "N";
}

Array::Array(const Array &arr, std::string s)
{
    set(arr);
    name = s;
}

Array::~Array()
{
    delete [] a;
}


/*****************************************
 *其他函数

*****************************************/
int Array::size() const
{
    return length;
}

int& Array::operator[] (int n)
{
    return a[n];
}

int Array::get(int n) const
{
    return a[n];
}

void Array::setName(std::string s)
{
    name = s;
}

Array Array::operator= (const Array &arr)
{
    delete [] a;
    set(arr);
    return *this;
}


Array Array::sub(int b, int e) const
{
    Array res(e-b+1);
    for (int i = 0; i < res.size(); i++)
        res[i] = a[b+i];

    return res;
}



/****************************************************
 *private

*****************************************************/
void Array::set(int n)
{
    a = new int[n];
    length = n;
}

void Array::set(const Array &arr)
{
    a = new int[arr.size()];
    length = arr.size();
    for (int i = 0; i < length; i++)
        a[i] = arr.a[i];
}
