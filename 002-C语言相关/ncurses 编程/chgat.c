/*mvchgat()用法示例：*/
#include<menu.h>
#include<stdlib.h>
#include<stdio.h>
#include<ncurses.h>
#include<string.h>

int main()
{
    initscr(); /*初始化并进入curses模式*/
    start_color(); /*开启颜色管理功能 */
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    printw("A Big string which I didn't care to type fully");
    mvchgat(0, 0, -1, A_BLINK, 1, NULL);
    /*
    *第一、二个参数表明了函数开始的位置。
    *第三个参数是被改变修饰的字符的数目，­1 表示一整行。
    *第四个参数是被改变的修饰名。
    *第五个参数是颜色索引。颜色索引已经在 init_pair()中被初试化了。
    *如果用０表示不使用颜色。
    *最后一个总是 NULL，没什么特殊含义。
    */
    
    refresh();
    getch();
    endwin();  //结束并退出curse模式
    return 0;
}
