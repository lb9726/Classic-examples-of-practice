/*多选菜单的例子*/
#include<menu.h>
#include<stdlib.h>
#include<stdio.h>
#include<ncurses.h>
#include<string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = 
{
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Choice 5",
    "Choice 6",
    "Choice 7",
    "Exit",
};

int main()
{
    ITEM ** my_items;
    int c;
    MENU *my_menu;
    WINDOW *my_menu_win;
    int n_choices,i;
    ITEM *cur_item;
    
    /*初始化 curses*/
    initscr();
    //start_color();
    cbreak;
    noecho();
    keypad(stdscr, TRUE);
    
    /*创建菜单项*/
    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices+1, sizeof(ITEM *));
    for (i = 0; i < n_choices; ++i)
    {
        my_items[i] = new_item(choices[i], choices[i]);
    }
    my_items[n_choices] = (ITEM *)NULL;
    /*创建菜单*/
    my_menu = new_menu((ITEM **)my_items);
    
    /*设置菜单为多值菜单*/
    menu_opts_off(my_menu, O_ONEVALUE);
    
    mvprintw(LINES - 3, 0, "User <SPACE> to select or unselect an item.");
    mvprintw(LINES - 2, 0, "<ENTER> to see presently selected item(F3 to Exit)");
    /*传递菜单*/
    post_menu(my_menu);
    refresh();
    
    while(( c = getch()) != KEY_F(3))
    {
        switch(c)
        {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case ' ':
                menu_driver(my_menu, REQ_TOGGLE_ITEM);
                break;
            case 10: /*Enter键*/
            {
                char temp[200];
                ITEM **items;
                
                items = menu_items(my_menu);
                temp[0] = '\0';
                for(i = 0; i < item_count(my_menu); ++i)
                {
                    if (item_value(items[i]) == TRUE)
                    {
                        strcat(temp, item_name(items[i]));
                        strcat(temp, " ");
                    }
                    move(20, 0);
                    clrtoeol();
                    mvprintw(20, 0, temp);
                    refresh();
                }
            }
            break;
        }
    }
    free_item(my_items[0]);
    free_item(my_items[1]);
    free_menu(my_menu);
    endwin();
}







