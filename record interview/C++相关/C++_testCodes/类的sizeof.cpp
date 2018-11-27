#include <iostream>
using namespace std;

class Base
{
    
};

class Son
{
    char a;
    int b;
    void F()
    {
        cout <<"is Fuction F()"<<endl;
    }
};

int main()
{
    Base b;
    cout<<"sizeof(b) = "<< sizeof(b) <<endl;
    Son s;
    cout<<"sizeof(s) = "<< sizeof(s) <<endl;
    return 0;
}
