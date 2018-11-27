/*带边框的窗口*/
#include<menu.h>
#include<stdlib.h>
#include<stdio.h>
#include<ncurses.h>
#include<string.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{
    WINDOW *my_win;
    int startx, starty, width, height;
    int ch;
    initscr();            /* 初始化并进入 curses 模式 */
    cbreak;               /* 行缓冲禁止，传递所有控制信息 */
    keypad(stdscr, TRUE); 
    
    height = 3;
    width = 10;
    starty = (LINES - height) / 2; /*计算窗口中心位置的行数 */
    startx = (COLS - width) / 2;   /*计算窗口中心位置的列数 */
    printw("Press F3 to exit");
    refresh();
    
    my_win = create_newwin(height, width, starty, startx);
    
    while(( ch = getch()) != KEY_F(3))
    {
        switch(ch)
        {
            case KEY_LEFT:
                destroy_win(my_win);
                my_win = create_newwin(height, width, starty, --startx);
                break;
            case KEY_RIGHT:
                destroy_win(my_win);
                my_win = create_newwin(height, width, starty, ++startx);
                break;
            case KEY_DOWN:
                destroy_win(my_win);
                my_win = create_newwin(height, width, ++starty, startx);
                break;
            case KEY_UP:
                destroy_win(my_win);
                my_win = create_newwin(height, width, --starty, startx);
                break;    
        }
    }
    endwin();
    return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);  /* 0, 0 是字符默认的行列起始位置 */
    wrefresh(local_win);    /*刷新窗口缓冲，显示 box */
    return local_win;
}


void destroy_win(WINDOW *local_win)
{
    /* box(local_win, ' ', ' ');不会按照预期的那样清除窗口边框。 而是在窗口的四个角落留下残
余字符*/
    wborder(local_win, ' ', ' ', ' ' , ' ' , ' ' , ' ' , ' ' ,' ');
    /*参数注解 9.3：
* 1. win:当前操作的窗口
* 2. ls:用于显示窗口左边界的字符
* 3. rs:用于显示窗口右边界的字符
* 4. ts:用于显示窗口上边界的字符
* 5. bs:用于显示窗口下边界的字符
* 6. tl:用于显示窗口左上角的字符
* 7. tr:用于显示窗口右上角的字符
* 8. bl:用于显示窗口左下角的字符
* 9. br:用于显示窗口右下角的字符
*/

    wrefresh(local_win);
    delwin(local_win);
}












