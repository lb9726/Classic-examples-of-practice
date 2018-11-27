#include <iostream>  
   
class TestObject {  
 public:  
  TestObject() {  
    std::cout << "TestObject() is called:"  
      << con_call_num_++<< std::endl;  
  }  
  TestObject(int _x) {  
    x_ = _x;  
    std::cout << "TestObject(int) is called:"  
      << con_call_num_++<< std::endl;  
  }  
  TestObject (TestObject & to) {  
    x_ = to.x_;  
    std::cout << "TestObject(TestObject) is called:"  
      << ccon_call_num_++ << std::endl;  
  }  
  TestObject (const TestObject& to) {  
    x_ = to.x_;  
    std::cout << "TestObject(const TestObject) is called:"  
      << ccon_call_num_++ << std::endl;  
  }  
  TestObject &operator =(const TestObject& to) {  
    if (&to == this)  
      return *this;  
    x_ = to.x_;  
    std::cout << "operator =(const) is called:"  
      << equal_call_num_++ << std::endl;  
    return *this;  
  }  
  TestObject &operator =(TestObject& to) {  
    if (&to == this)  
      return *this;  
    x_ = to.x_;  
    std::cout << "operator =() is called:"  
      << equal_call_num_++ << std::endl;  
    return *this;  
  }  
  ~TestObject() {  
    std::cout << "~TestObject() is called:"  
      << des_call_num_++ << std::endl;  
  }  
 private:  
  int x_;  
  static int con_call_num_;  
  static int ccon_call_num_;  
  static int equal_call_num_;  
  static int des_call_num_;  
};  
   
int TestObject::con_call_num_ = 0;  
int TestObject::ccon_call_num_ = 0;  
int TestObject::equal_call_num_ = 0;  
int TestObject::des_call_num_ = 0;  
   
int main() {  
  // copy  
  TestObject to_1;  
  TestObject to_2(1);  
  TestObject to_3 = 1;  
  TestObject to_4 = to_2;  
  TestObject to_5(to_4);  
  // assign  
  to_1 = to_2;  
  return 0;  
} 
