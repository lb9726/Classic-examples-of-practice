#include <iostream>
#include "Singleton.h"
using namespace std;

int main(int argc, char *argv[])
{
	Singleton * sg = Singleton::getInstance();
	sg->singletonOperation();
//	if (NULL != sg)  // 会造成死循环，递归删除，因为delete 会自动调用系构函数
//    {
//        delete sg;
//        sg = NULL;
//    }
    delete sg;
	return 0;
}
