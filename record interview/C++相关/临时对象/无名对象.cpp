#include <iostream>

using namespace std;


class ref
{
    public:
        ref(int input);
        ~ref();
        int i;
        void change();
        void change_const() const;

};
void ref::change_const() const
{
    cout<<"in change_const"<<endl;
}
void ref::change() 
{
    i=3;
    cout<<"in change"<<endl;
}
ref::ref(int input)
{
    i=input;
}
ref::~ref()
{
    cout<<"tear down"<<endl;
}


void test_const(const string & str)
{
    cout<<str<<endl;
}

void test(string & str)
{
    cout<<str<<endl;
}

main()
{
//  int &i=1;//不能用非对象去初始化一个引用。
    const int &j=1;//这样可以，但是没什么实际意义


    string str("haha");
    test(str);
    test_const(str);


//    test(string("haha"));//报invalid initialization of non-const reference of type 'std::string&' from a temporary of type 'std::string'。使用临时对象不能初始化test的string & 引用。
    test_const(string("haha"));//使用临时对象初始化函数形参的时候，函数形参必须是有const限定。


    ref const obj(1);
    cout<<obj.i<<endl;
    obj.change_const();
    cout<<obj.i<<endl;
    ref(2).change();//无名对象调用非const函数,这说明无名对象（临时对象）并不能等同于用const修饰的有名对象，用const修饰的有名对象，是不允许调用非const方法的，因为那样会修改对象的成员。这可以从下面的例子看到。
//  obj.change();//const对象调用非const函数,报passing `const ref' as `this' argument of `void ref::change()' discards qualifiers
}
