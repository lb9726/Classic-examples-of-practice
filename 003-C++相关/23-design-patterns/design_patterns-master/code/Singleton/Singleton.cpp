///////////////////////////////////////////////////////////
//  Singleton.cpp
//  Implementation of the Class Singleton
//  Created on:      02-十月-2014 17:24:46
//  Original author: colin
///////////////////////////////////////////////////////////

#include "Singleton.h"
#include <iostream>
using namespace std;

Singleton * Singleton::instance = NULL;
Singleton::Singleton(){

}

Singleton::~Singleton(){
    cout << "delete instance" << endl;cout << "delete instance again" << endl;
//    if (NULL != instance)
//    {
//        delete instance;
//        instance = NULL;
//    }	也会造成死循环delete
//    delete instance;
//    instance = NULL;
}

Singleton* Singleton::getInstance(){
	if (instance == NULL)
	{
		instance = new Singleton();
	}
	
	return  instance;
}


void Singleton::singletonOperation(){
	cout << "singletonOperation" << endl;
}

