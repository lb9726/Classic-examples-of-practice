#include <iostream>
using namespace std;
class Lock  
{  
private:         
    CCriticalSection m_cs;  
public:  
    Lock(CCriticalSection  cs) : m_cs(cs)  
    {  
        m_cs.Lock();  
    }  
    ~Lock()  
    {  
        m_cs.Unlock();  
    }  
};  
  
class CSingleton  
{  
private:  
    CSingleton();  
    CSingleton(const CSingleton &);  
    CSingleton& operator = (const CSingleton &);  
  
public:  
    static CSingleton *Getinstance();  
    static CSingleton *m_Instance;  
    static CCriticalSection cs;  
};  

