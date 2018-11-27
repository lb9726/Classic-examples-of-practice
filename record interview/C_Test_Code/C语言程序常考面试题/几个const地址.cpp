#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

int main()
{
    char str1[] = "abc";
    char str2[] = "abc";
    const char str3[] = "abc";
    const char str4[] = "abc";
    const char* str5 = "abc";
    const char* str6 = "abc";
    cout << boolalpha << ( str1==str2 ) << endl; // 输出什么?
    cout << boolalpha << ( str3==str4 ) << endl; // 输出什么?
    cout << boolalpha << ( str5==str6 ) << endl; // 输出什么?
    return 0;
}

