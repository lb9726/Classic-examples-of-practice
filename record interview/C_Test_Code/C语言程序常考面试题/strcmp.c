#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int mystrcmp(const char *str1, const char *str2)
{
    if ((NULL == str1) ||(NULL == str2))
        return -2;
    int ret = 0;
    while (!(ret = *(unsigned char *)str1 - *(unsigned char *)str2) && (*str1 || *str2))
    {
        str1++;
        str2++;
    }
    if (ret < 0)
        return -1;
    else if (ret > 0)
        return 1;
    return 0;
}

int main()
{
    int a = mystrcmp("adb","add");
    int b = mystrcmp(NULL, NULL);
    int c = mystrcmp("ab", "ab");
    printf("a = %d , b = %d , c = %d\n", a, b, c );
    return 0;
}

/*
这个函数要注意一下几点
①使用*(unsignedchar*)str1而不是用*str1。这是因为传入的参数为有符号数，有符号字符值的范围是-128~127，无符号字符值的范围是0~255，而字符串的ASCII没有负值，若不转化为无符号数这回在减法实现时出现错误。例如str1的值为1，str2的值为255。
作为无符号数计算时ret=-254,结果为负值，正确作为有符号数计算时ret=2,结果为正值，错误
②While循环中ret=*(unsignedchar*)str1-*(unsignedchar*)str2)&&*str1，最后与上str1也可以换成str2，因为前面已经做了相减，无论哪个先为‘\0’都会退出。因为最后与上str1是为了判断str1是否结束，即是否为‘\0’。
③这个函数没有判断参数为NULL时的情况，所以当传入NULL时程序会崩溃。网上看别人说商业化代码都会在调用strcmp前先判断是否为NULL，所以可以不用判断NULL；我在VC6上测试string.h中的strcmp(NULL,NULL)，程序也会崩溃。这里可以根据实际情况来决定。
若要判断NULL按下面方法更改代码，可以在这个函数最前面加入断言assert((NULL!=str1)&&(NULL!=str2))
但要注意断言assert是仅在Debug版本起作用的宏，是在Debug时做的无害测试。若想在Release版也可
以判断NULL，那我们必须用别的代码来判断。可以在程序前面加入if判断
if((NULL!=str1)&&(NULL!=str2))
{
    return 0;
}
我用CFree5测试sting.h中的strcmp(NULL,NULL)，程序返回值为0（strcmp(NULL,str1)崩溃），这里我们可以返回其他的值如-2。我们也可以在函数前面加入while判断while((NULL!=str1)&&(NULL!=str2)){
//strcmp实现代码}
return0;
*/







