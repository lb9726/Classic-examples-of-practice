#include "spreadsheetcell.h"
#include <iostream>
#include <sstream>
using namespace std;

SpreadsheetCell::SpreadsheetCell() : mValue(0), mNumAccesses(0)
{
}

SpreadsheetCell::SpreadsheetCell(double initialValue) : mNumAccesses(0)
{
    set(initialValue);
}

SpreadsheetCell::SpreadsheetCell(const string& initialValue) :
    mValue(stringToDouble(initialValue)), mString(initialValue), mNumAccesses(0)
{
}

SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src)
{
    mValue = src.mValue;
    mString = src.mString;
    mNumAccesses = src.mNumAccesses;
}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
    if (this == &rhs)
    {
        return (*this);
    }
    mValue = rhs.mValue;
    mString = rhs.mString;
    mNumAccesses = rhs.mNumAccesses;
    return (*this);
}

void SpreadsheetCell::set(double inValue)
{
    mValue = inValue;
    mString = doubleToString(mValue);
}

void SpreadsheetCell::set(const string& inString)
{
    mString = inString;
    mValue = stringToDouble(mString);
}

string SpreadsheetCell::doubleToString(double inValue)
{
    ostringstream ostr;

    ostr << inValue;
    return (ostr.str());
}

double SpreadsheetCell::stringToDouble(const string& inString)
{
    double temp;

    istringstream istr(inString);

    istr >> temp;
    if (istr.fail() || !istr.eof())
    {
        return (0);
    }
    return (temp);
}

const SpreadsheetCell operator+(const SpreadsheetCell& lhs,
                                const SpreadsheetCell& rhs)
{
    SpreadsheetCell newCell;
    newCell.set(lhs.mValue + rhs.mValue); // call set to update mValue and mString
    return (newCell);
}

const SpreadsheetCell operator-(const SpreadsheetCell& lhs,
                                const SpreadsheetCell& rhs)
{
    SpreadsheetCell newCell;
    newCell.set(lhs.mValue - rhs.mValue); // call set to update mValue and mString
    return (newCell);
}

const SpreadsheetCell operator*(const SpreadsheetCell& lhs,
                                const SpreadsheetCell& rhs)
{
    SpreadsheetCell newCell;
    newCell.set(lhs.mValue * rhs.mValue); // call set to update mValue and mString
    return (newCell);
}

const SpreadsheetCell operator/(const SpreadsheetCell& lhs,
                                const SpreadsheetCell& rhs)
{
    SpreadsheetCell newCell;
    if (rhs.mValue == 0)
    {
        newCell.set(0); // call set to update mValue and mString
    }
    else
    {
        newCell.set(lhs.mValue / rhs.mValue); // call set to update mValue
        // and mString
    }
    return (newCell);
}

SpreadsheetCell& SpreadsheetCell::operator+=(const SpreadsheetCell& rhs)
{
    set(mValue + rhs.mValue); // call set to update mValue and mString
    return (*this);
}

SpreadsheetCell& SpreadsheetCell::operator-=(const SpreadsheetCell& rhs)
{
    set(mValue - rhs.mValue); // call set to update mValue and mString
    return (*this);
}

SpreadsheetCell& SpreadsheetCell::operator*=(const SpreadsheetCell& rhs)
{
    set(mValue * rhs.mValue); // call set to update mValue and mString
    return (*this);
}

SpreadsheetCell& SpreadsheetCell::operator/=(const SpreadsheetCell& rhs)
{
    set(mValue / rhs.mValue); // call set to update mValue and mString
    return (*this);
}

bool operator==(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return (lhs.mValue == rhs.mValue);
}

bool operator<(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return (lhs.mValue < rhs.mValue);
}

bool operator>(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return (lhs.mValue > rhs.mValue);
}

bool operator!=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return (lhs.mValue != rhs.mValue);
}

bool operator<=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return (lhs.mValue <= rhs.mValue);
}

bool operator>=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return (lhs.mValue >= rhs.mValue);
}

/*
    operator-不会改变操作数，因此这个方法必须构造一个对原值取负数的新SpreadsheetCell，
    并返回该对象的一个副本。因此，它不能返回一个引用
*/
const SpreadsheetCell SpreadsheetCell::operator-() const
{
    SpreadsheetCell newCell(*this);
    newCell.set(-mValue); // call set to update mValue and mStr
    return (newCell);
}
/*
    C++标准指定自增和自减的前缀版本返回一个左值，因此它们不能返回const值。前缀形式的返回值与操作数的最后值相同，
    因此前缀自增和自减可以返回调用此操作符的对象的一个引用。
    不过，自增和自减的后缀版本返回的值与操作数的最后值不同，
    因此它们不能返回引用。
*/
//  前++不带参数int，后++带参数int
//  前++
SpreadsheetCell& SpreadsheetCell::operator++()
{
    set(mValue + 1);
    return (*this);
}

// 前++不带参数int，后++带参数int
// 后++
const SpreadsheetCell SpreadsheetCell::operator++(int)
{
    SpreadsheetCell oldCell(*this); // save the current value before incrementing
    set(mValue + 1); // increment
    return (oldCell); // return the old value
}

// 前--
SpreadsheetCell& SpreadsheetCell::operator--()
{
    set(mValue - 1);
    return (*this);
}

// 后--
const SpreadsheetCell SpreadsheetCell::operator--(int)
{
    SpreadsheetCell oldCell(*this); // save the current value before incrementing
    set(mValue - 1); // increment
    return (oldCell); // return the old value
}
