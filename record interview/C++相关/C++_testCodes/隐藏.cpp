#include <iostream>
using namespace std;
class CBase  
{  
public:  
    virtual void A(int ival){cout <<" CBase::A() ";}  
    void B(int ival){cout<<" CBase::B() ";}  
    void C(int ival){cout<<" CBase::C() ";}  
    int D(int ival) { cout << "CBase::D()";}
};  
  
class CDerive : public CBase  
{  
public:  
    virtual void A(int ival)    //覆盖父类的A：函数名、参数完全相同，且父类一定要有virtual  
    {
        cout<< " CDerive::A() ";
    }      
  
    void B(int ival)            //隐藏父类的B：函数名、参数完全相同，且父类无virtual  
    {
        cout<< " CDerive::B() ";
    }      
  
    void C(float ival)          //隐藏父类的C：函数名相同、与数不同，与virtual无关  
    {
        cout << " CDerive::C() ";
    }
    
    void D(int ival)
    {
    	cout << " CDerive::D() ";
    }      
  
};  
  
int main()  
{  
    CDerive d;  
    CBase* pB = &d;  
      
    d.A(1);       //均调用子类的A
    pB->A(1);
    cout<<endl;     
    
    d.B(1);       //分别调用各自的B
    pB->B(1);
    cout<<endl;     
    
    d.C(1);      //分别调用各自的C 
    pB->C(1);
    cout<<endl;    
  
  	d.D(1);     //分别调用各自的D 
  	pB->D(1);   // 函数返回值不同，函数名相同参数列表也相同时也不能造成隐藏
  	cout<< endl;
    return 0;  
}


/*
运行结果：
 CDerive::A()  CDerive::A() 
 CDerive::B()  CBase::B() 
 CDerive::C()  CBase::C() 
 CDerive::D() CBase::D()
*/



