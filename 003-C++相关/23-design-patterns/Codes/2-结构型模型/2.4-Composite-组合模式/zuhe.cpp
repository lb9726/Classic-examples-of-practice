#include <stdio.h>  
#include <vector>  
//c++ 23种设计模式之组合模式  
//适用情况：1、表示对象的部分/整体层次结构 2、忽略组合对象和个体对象的不同  
namespace DesignPattern_Composite  
{  
    //组件  
    class Component  
    {  
  
    public:  
        virtual void Operation()=0;  
        virtual void Add(Component *p){}  
  
    };  
  
    //个体类  
    class Leaf:public Component  
    {  
  
    public:  
        virtual void Operation(){ printf("我是个体类!\n");}  
  
    };  
    //整体类  
    class Composite:public Component  
    {  
          
    public:  
        virtual void Add(Component *p){   
              
            _list.push_back(p);  
        }  
        virtual void Operation()  
        {  
              
            std::vector<Component *>::const_iterator it;  
            for(it=_list.begin();it!=_list.end();it++)  
            {  
                  
                (*it)->Operation();  
            }  
        }  
          
    private:  
        std::vector <Component*> _list;  
  
  
    };  
  
}  

int main() 
{ 
    using namespace DesignPattern_Composite; 
    Component *pc1 = new Leaf(); 
    Component *pc2 = new Leaf; 
    Leaf *pc4 = new Leaf; 
 
    Composite *pc3 = new Composite(); 
    pc3->Add(pc1); 
    pc3->Add(pc2); 
    pc3->Add(pc4); 
    pc3->Operation(); 
 
 
    printf("\n\n\n"); 
    Composite *pc5 = new Composite; 
    pc5->Add(pc4); 
    pc5->Add(pc2); 
    pc5->Add(pc1); 
    pc5->Operation(); 
 
} 
