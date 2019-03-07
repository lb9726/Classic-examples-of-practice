#include <iostream>  
using namespace std;  
  
class A  
{  
public:  
    int x;  
     A get() const
    {  
        return *this; //返回当前对象的拷贝  
    }  
};  
  
int main()  
{  
    A a;  
    a.x = 4;  
  
    if(a.x == a.get().x)  
    {  
        cout << a.x << endl;  
    }  
    else  
    {  
        cout << "no" << endl;  
    }  
  
    if(&a == &a.get())  
    {  
        cout << "yes" << endl;  
    }  
    else  
    {  
        cout << "no" << endl;  
    }  
  
    return 0;  
}  
