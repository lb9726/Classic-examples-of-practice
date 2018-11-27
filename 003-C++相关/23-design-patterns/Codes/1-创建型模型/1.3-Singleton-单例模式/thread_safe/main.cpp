#include "instance.h"
using namespace std;
CSingleton* CSingleton::m_Instance = 0;  
  
CSingleton* CSingleton::Getinstance()  
{  
    if(m_Instance == NULL)  
    {   //double check  
        Lock lock(cs);           //用lock实现线程安全，用资源管理类，实现异常安全  
        //使用资源管理类，在抛出异常的时候，资源管理类对象会被析构，析构总是发生的无论是因为异常抛出还是语句块结束。  
        if(m_Instance == NULL)  
        {  
            m_Instance = new Singleton();  
        }  
    }  
    return m_Instance;  
}

int main()
{
    cout << "CSingleton::Getinstance()1 = " << CSingleton::Getinstance();
    cout << "CSingleton::Getinstance()2 = " << CSingleton::Getinstance();
    return 0;
}
