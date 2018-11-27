#include <iostream>
#include <string>
using namespace std;

class Base
{
private:
    string baseName = "base";
public:
    Base()
    {
        cout << "Base()"<< endl;
        callName();
    }
    ~Base()
    {
        cout << "~Base()"<< endl;
    }
    void callName()
    {
        cout << "baseName = "<<baseName << endl;
    }
};

class Sub:public Base
{
private:
     string baseName = "sub";
public:
    Sub()
    {
        cout << "Sub()"<< endl;
        callName();
    }
    ~Sub()
    {
        cout << "~Sub()"<< endl;
    }
    void callName()
    {
        cout << "Sub baseName = "<<baseName << endl;
    }     
};
int main()
{
    Base *b = new Sub();
    return 0;
}

/*
libo@ubuntu:~/Desktop$ g++ c++.cpp -o ./Executive/c
c++.cpp:8:23: warning: non-static data member initializers only available with -std=c++11 or -std=gnu++11 [enabled by default]
     string baseName = "base";
                       ^
c++.cpp:28:24: warning: non-static data member initializers only available with -std=c++11 or -std=gnu++11 [enabled by default]
      string baseName = "sub";
                        ^


g++ c++.cpp -o ./Executive/c -std=c++11
不会报警告

libo@ubuntu:~/Desktop$ g++ c++.cpp -o ./Executive/c -std=c++11
libo@ubuntu:~/Desktop$ ./Executive/c
Base()
baseName = base
Sub()
Sub baseName = sub
libo@ubuntu:~/Desktop$
*/
