#include "./include/formatPrintf.h"
int main()
{
    STNODE *head = NULL;
    head = readFileToList("test.txt");
    showInfoInorder(head); // 调用函数接口实现功能
    destroyLinklist(head); // 释放链表分配的资源
    return 0;
}
