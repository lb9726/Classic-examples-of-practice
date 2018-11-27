#ifndef __SINGLEON_H__
#define __SINGLEON_H__
#include<iostream>
using namespace std;

class singleton
{
public:
	static singleton* Instance();
	int getnumber() const;
	void setnumber(int num);
protected:
	singleton();
private:
	static singleton* _instance;
    static int a;
};

#endif //__SINGLEON_H__


//	static singleton* _instance; 第15行的 //	static singleton* _instance;如果注释了则会出现
/*
singleton.cpp:3:24: error: ‘singleton* singleton::_instance’ is not a static member of ‘class singleton’
 singleton* singleton:: _instance = NULL;
                        ^
singleton.cpp: In static member function ‘static singleton* singleton::Instance()’:
singleton.cpp:12:14: error: ‘_instance’ was not declared in this scope
  if (NULL == _instance)
              ^
singleton.cpp:16:9: error: ‘_instance’ was not declared in this scope
  return _instance;
         ^
*/
