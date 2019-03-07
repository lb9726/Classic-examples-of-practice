#include <iostream>  
using namespace std;  
  
class A  
{  
public:  
    int mValue;
    bool operator==(const A& lhs)
    {
        return (lhs.mValue == this->mValue);
    } 
    A* getPointer()  
    {  
        return this;  
    }
    A getClone()
    {
        return *this;
    }
    A & getReference()
    {
        return *this;
    } 
};  
  
int main()  
{  
    A a;  
    a.mValue = 4;  
  
    if (&a == a.getPointer())  
    {  
        cout << "yes" << endl;  
    }  
    else  
    {  
        cout << "no" << endl;  
    } 

    if (a == a.getClone())  
    {  
        cout << "yes" << endl;  
    }  
    else  
    {  
        cout << "no" << endl;  
    }
    
    if (a == a.getReference())  
    {  
        cout << "yes" << endl;  
    }  
    else  
    {  
        cout << "no" << endl;  
    }
    return 0;  
}  
