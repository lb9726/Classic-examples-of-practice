#include<stdio.h>
#include<stdlib.h>

int main()
{
    extern void enter_string(char str[80]);
    extern void delete_string(char str[], char ch);
    extern void print_string(char str[]);
    /*以上3行声明在本函数中将要调用在其他文件中定义的三个函数*/
    
    char c;
    char str[80];
    printf("please enter string: ");
    enter_string(str);
    you_hua(str);
    printf("please enter a character to delete: ");
    scanf("%c", &c);
    delete_string(str, c);
    print_string(str);
}
