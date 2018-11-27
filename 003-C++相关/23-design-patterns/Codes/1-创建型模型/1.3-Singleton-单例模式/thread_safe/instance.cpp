#include <iostream>

using namespace std;  

class Singleton        
{    
public:    
    static Singleton *GetInstance();    
private:    
    Singleton()      
    {          
        cout << "Singleton ctor" << endl;          
    }  
    
    ~Singleton()      
    {         
        cout << "Singleton dtor" << endl;         
    }  
    
    static Singleton *m_pInstance;

    class Garbo              
    {          
    public:          
        ~Garbo()         
        {             
            if (NULL != Singleton::m_pInstance)
            {                  
                cout << "Garbo dtor" << endl;                  
                delete Singleton::m_pInstance;                 
            }              
        }          
    };  
    
    static Garbo garbo;      
};  

Singleton::Garbo Singleton::garbo;  // 一定要初始化，不然程序结束时不会析构garbo  

Singleton *Singleton::m_pInstance = NULL;  

Singleton *Singleton::GetInstance()  
{    
    if (m_pInstance == NULL)
    {
        m_pInstance = new Singleton;
    }          
    return m_pInstance;  
    
}  

int main()  
{      
    Singleton *p1 = Singleton::GetInstance();      
    Singleton *p2 = Singleton::GetInstance();       
    if (p1 == p2)  
    {
        cout << "p1 == p2" << endl;  
    }
    return 0;     
}
