#include <iostream>  
using namespace std;  
  
class A  
{  
public:  
    int x;  
    A* get()  
    {  
        cout <<"this = "<< this<<endl;
        cout <<"*this = " << *this<<endl;
        return this;  
    }
    friend ostream& operator<<(ostream& ostr, const A& cell);
    friend istream& operator>>(istream& istr, A& cell); 
};  
  
int main()  
{  
    A a;  
    a.x = 4;  
    
    if(&a == a.get())  
    {  
        cout << "yes" << endl;  
    }  
    else  
    {  
        cout << "no" << endl;  
    }  
  
    return 0;  
}  
