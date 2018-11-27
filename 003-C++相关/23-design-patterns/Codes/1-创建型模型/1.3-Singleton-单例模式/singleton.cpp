#include "singleton.h"

singleton* singleton:: _instance = NULL;
int singleton::a = 0;
singleton::singleton()
{
	cout << "*singleton..." << endl;
}

singleton* singleton::Instance()
{
	if (NULL == _instance)
	{
		_instance = new singleton();
	}
	return _instance;
}

int singleton::getnumber() const
{
	return a;
}

void singleton::setnumber(int num)
{
	a = num;
}

/*
//singleton* singleton:: _instance = NULL;  注释掉第三行的代码，则会提示如下错误 
devin@ubuntu:~/Desktop/Repository/23-design-patterns/23-design-patterns/Codes/单例模式$ g++ *.cpp -o 1
/tmp/ccLLKrnV.o: In function `singleton::Instance()':
singleton.cpp:(.text+0x34): undefined reference to `singleton::_instance'
singleton.cpp:(.text+0x55): undefined reference to `singleton::_instance'
singleton.cpp:(.text+0x5c): undefined reference to `singleton::_instance'
/tmp/ccLLKrnV.o: In function `singleton::getnumber() const':
singleton.cpp:(.text+0x88): undefined reference to `singleton::a'
/tmp/ccLLKrnV.o: In function `singleton::setnumber(int)':
singleton.cpp:(.text+0x9e): undefined reference to `singleton::a'
collect2: error: ld returned 1 exit status
devin@ubuntu:~/Desktop/Repository/23-design-patterns/23-design-patterns/Codes/单例模式$ 
*/
