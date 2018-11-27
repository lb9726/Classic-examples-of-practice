#include<menu.h>
#include<stdlib.h>
#include<stdio.h>
#include<ncurses.h>
#include<string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = 
{
    "Choice 1","Choice 2","Choice 3","Choice 4","Choice 5",
    "Choice 6","Choice 7","Choice 8","Choice 9","Choice 10",
    "Choice 11","Choice 12","Choice 13","Choice 14","Choice 15",
    "Choice 16","Choice 17","Choice 18","Choice 19","Choice 20",
    "Exit",
    (char *)NULL,
};

int main()
{
    ITEM ** my_items;
    int c;
    MENU *my_menu;
    WINDOW *my_menu_win;
    int n_choices,i;
    
    /*初始化 curses*/
    initscr();
    start_color();
    cbreak;
    noecho();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2,COLOR_CYAN,COLOR_BLACK);
    /*创建菜单项*/
    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
    for (i = 0; i < n_choices; ++i)
    {
        my_items[i] = new_item(choices[i], choices[i]);
    }
    /*创建菜单*/
    my_menu = new_menu((ITEM **)my_items);
    
    /* 创建与菜单相关联的窗口*/
    my_menu_win = newwin(10, 70, 4, 4);
    keypad(my_menu_win, TRUE);
    
    /* 设置主窗口和子窗口 */
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 6, 68, 3, 1));
    set_menu_format(my_menu, 5, 3);
    /* 设置字符串的标记为 " * " */
    set_menu_mark(my_menu," * ");
    
    /* 在主窗口的边界打印边框线和标题 */
    box(my_menu_win, 0 ,0);
    attron(COLOR_PAIR(2));
    mvprintw(LINES - 3, 0, "User PageUp and PageDown to Scorll");
    mvprintw(LINES - 2, 0, "User Arrowkeys to navigate(F3 to Exit)");
    attroff(COLOR_PAIR(2));
    refresh();
    
    /*传递菜单*/
    post_menu(my_menu);
    wrefresh(my_menu_win);
    
    while(( c = wgetch(my_menu_win)) != KEY_F(3))
    {
        switch(c)
        {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(my_menu, REQ_LEFT_ITEM);
                break;
            case KEY_RIGHT:
                menu_driver(my_menu, REQ_RIGHT_ITEM);
                break;    
            case KEY_NPAGE:
                menu_driver(my_menu, REQ_SCR_DPAGE);
                break;
            case KEY_PPAGE:
                menu_driver(my_menu, REQ_SCR_UPAGE);
                break;
        }
        wrefresh(my_menu_win);
    }
    /* 取消递送并释放占用的内存 */
    unpost_menu(my_menu);
    free_menu(my_menu);
    for (i = 0; i < n_choices; ++i)
    {
        free_item(my_items[i]);
    }
    endwin();
}
    
    
