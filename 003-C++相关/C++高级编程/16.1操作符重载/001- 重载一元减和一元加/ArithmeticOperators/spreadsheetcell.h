#ifndef SPREADSHEETCELL_H
#define SPREADSHEETCELL_H

#include <string>
using std::string;

class SpreadsheetCell
{
public:
    SpreadsheetCell();
    SpreadsheetCell(double initialValue);
    explicit SpreadsheetCell(const string& initialValue);
    SpreadsheetCell(const SpreadsheetCell& src);
    SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
    void set(double inValue);
    void set(const string& inString);

    double getValue() const {mNumAccesses++; return (mValue); }
    string getString() const {mNumAccesses++; return (mString); }

    static string doubleToString(double inValue);
    static double stringToDouble(const string& inString);

    friend const SpreadsheetCell operator+(const SpreadsheetCell& lhs,
                                           const SpreadsheetCell& rhs);
    friend const SpreadsheetCell operator-(const SpreadsheetCell& lhs,
                                           const SpreadsheetCell& rhs);
    friend const SpreadsheetCell operator*(const SpreadsheetCell& lhs,
                                           const SpreadsheetCell& rhs);
    friend const SpreadsheetCell operator/(const SpreadsheetCell& lhs,
                                           const SpreadsheetCell& rhs);
    SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
    SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
    SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
    SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);
    friend bool operator==(const SpreadsheetCell& lhs,
                           const SpreadsheetCell& rhs);
    friend bool operator<(const SpreadsheetCell& lhs,
                          const SpreadsheetCell& rhs);
    friend bool operator>(const SpreadsheetCell& lhs,
                          const SpreadsheetCell& rhs);
    friend bool operator!=(const SpreadsheetCell& lhs,
                           const SpreadsheetCell& rhs);
    friend bool operator<=(const SpreadsheetCell& lhs,
                           const SpreadsheetCell& rhs);
    friend bool operator>=(const SpreadsheetCell& lhs,
                           const SpreadsheetCell& rhs);
    const SpreadsheetCell operator-() const;
    SpreadsheetCell& operator++(); // prefix
    const SpreadsheetCell operator++(int); // postfix
    SpreadsheetCell& operator--(); // prefix
    const SpreadsheetCell operator--(int); // postfix

protected:
    double mValue;
    string mString;

    mutable int mNumAccesses;
};

#endif // SPREADSHEETCELL_H

/* https://blog.csdn.net/starlee/article/details/1430387
 mutalbe的中文意思是“可变的，易变的”，跟constant（既C++中的const）是反义词。
    在C++中，mutable也是为了突破const的限制而设置的。被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中。
    我们知道，如果类的成员函数不会改变对象的状态，那么这个成员函数一般会声明成const的。
    但是，有些时候，我们需要在const的函数里面修改一些跟类状态无关的数据成员，那么这个数据成员就应该被mutalbe来修饰。

类ClxTest的成员函数Output是用来输出的，不会修改类的状态，所以被声明为const的。
    函数OutputTest也是用来输出的，里面调用了对象lx的Output输出方法，
    为了防止在函数中调用其他成员函数修改任何成员变量，所以参数也被const修饰。
    如果现在，我们要增添一个功能：计算每个对象的输出次数。如果用来计数的变量是普通的变量的话，
    那么在const成员函数Output里面是不能修改该变量的值的；
    而该变量跟对象的状态无关，所以应该为了修改该变量而去掉Output的const属性。
    这个时候，就该我们的mutable出场了——只要用mutalbe来修饰这个变量，所有问题就迎刃而解了。
    计数器m_iTimes被mutable修饰，那么它就可以突破const的限制，在被const修饰的函数里面也能被修改。
*/
