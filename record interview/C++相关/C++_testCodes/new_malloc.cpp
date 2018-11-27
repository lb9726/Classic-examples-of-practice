#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
class Obj  
{  
public:  
    Obj()   
    { 
        cout  <<  "Initialization"  <<  endl; 
    }  
    ~ Obj()  
    { 
        cout  <<  "Destroy" <<  endl; 
    }  
    void Initialize()  
    { 
        cout  <<  "Initialization"  <<  endl; 
    }  
    void  Destroy()  
    { 
        cout  <<  "Destroy"  <<  endl; 
    }  
}obj;
  
void  UseMallocFree()  
{  
    Obj* a  =  (Obj *)malloc(sizeof(obj));      //  allocate memory   
    //a -> Initialize();                        //  initialization  
    // …   
    a -> Destroy();                             // deconstruction   
    free(a);                                    // release memory  
    printf("\n\n");
}
  
void  UseNewDelete(void)  
{  
    Obj *a  =   new  Obj;                                             
    // …   
    delete a;   
}

int main()
{
    UseMallocFree();
    UseNewDelete();
    return 0;
}

/*
类Obj的函数Initialize实现了构造函数的功能，函数Destroy实现了析构函数的功能。函数UseMallocFree中，由于malloc/free不能执行构造函数与析构函数，必须调用成员函数Initialize和Destroy来完成“构造”与“析构”。所以我们不要用malloc/free来完成动态对象的内存管理，应该用new/delete。由于内部数据类型的“对象”没有构造与析构的过程，对它们而言malloc/free和new/delete是等价的。

2、联系
既然new/delete的功能完全覆盖了malloc/free，为什么C++还保留malloc/free呢？因为C++程序经常要调用C函数，而C程序只能用malloc/free管理动态内存。如果用free释放“new创建的动态对象”，那么该对象因无法执行析构函数而可能导致程序出错。如果用delete释放“malloc申请的动态内存”，理论上讲程序不会出错，但是该程序的可读性很差。所以new/delete、malloc/free必须配对使用。
*/





