#include<iostream>
using namespace std;

class CSingleton    
{    
private:    
    CSingleton()      
    {    
    }    
public:    
    static CSingleton * GetInstance()    
    {    
        static CSingleton instance;     
        return &instance;    
    }
public:
	int ia;   
}; 

int main()
{
	CSingleton* a2 = CSingleton::GetInstance();
	a2->ia = 200;
	CSingleton* b2 = CSingleton::GetInstance();
	cout << b2->ia << endl;
}

/*


饿汉式
       饿汉式的特点是一开始就加载了，如果说懒汉式是“时间换空间”，那么饿汉式就是“空间换时间”，因为一开始就创建了实例，所以每次用到的之后直接返回就好了。

饿汉式是线程安全的,在类创建的同时就已经创建好一个静态的对象供系统使用,以后不再改变，懒汉式如果在创建实例对象时不加上synchronized则会导致对对象的访问不是线程安全的。
注：线程安全的通俗解释 - 不管多个线程是怎样的执行顺序和优先级,或是wait,sleep,join等控制方式，如果一个类在多线程访问下运转一切正常，并且访问类不需要进行额外的同步处理或者协调，那么我们就认为它是线程安全的。 线程安全的类应当封装了所有必要的同步操作，调用者无需额外的同步。还有一点：无状态的类永远是线程安全的。
        
         在饿汉式的单例类中，其实有两个状态，单例未初始化和单例已经初始化。假设单例还未初始化，有两个线程同时调用GetInstance方法，这时执行 m_pInstance == NULL 肯定为真，然后两个线程都初始化一个单例，最后得到的指针并不是指向同一个地方，不满足单例类的定义了，所以饿汉式的写法会出现线程安全的问题！在多线程环境下，要对其进行修改。
*/
