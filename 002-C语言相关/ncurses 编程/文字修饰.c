/*文字修饰的例子*/
#include<menu.h>
#include<stdlib.h>
#include<stdio.h>
#include<ncurses.h>
#include<string.h>

int main(int argc, char *argv[])
{
    int ch, prev;
    FILE *fp;
    int goto_prev = FALSE, y , x;
    
    if (2 != argc)
    {
        printf("Usage:%s <a c file name>\n",argv[0]);
        exit(1);
    }
    
    fp = fopen(argv[1], "r");
    if (NULL == fp)
    {
        perror("Cannot open input file");
        exit(1);
    }
    
    initscr();  /*初始化并进入curses模式*/
    prev = EOF;
    while(EOF != (ch = fgetc(fp)))
    {
        if (prev == '/' && ch == '*') /*当读到字符"/"和"*"的时候开启修饰*/
        {
            attron(A_BOLD); /*将/和*及以后输出的文字字体加粗*/
            goto_prev = TRUE;
        }
        if (goto_prev == TRUE)
        {
            getyx(stdscr, y, x);
            move(y, x-1);
            printw("%c%c",'/',ch); /*打印实际内容的部分*/
            ch = 'a'; //避免下次读取变量错误，这里赋一个任意值
            goto_prev = FALSE; //让这段程序只运行一次
        }
        else 
            printw("%c", ch);
        refresh();   //将缓冲区的内容刷新到屏幕上
        
        if (prev == '*' && ch == '/')
            attroff(A_BOLD);   //当读到字符* 和 / 的时候关闭修饰   
        prev = ch;
    }
    getch();
    endwin(); //结束并退出curse模式
    return 0;
}









