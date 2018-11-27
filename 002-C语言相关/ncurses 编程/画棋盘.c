    #include<unistd.h>  
    #include<stdlib.h>  
    #include<ncurses.h>  
       
    int main()  
    {  
        int i;  
      
        initscr();              //初始化屏幕  
      
        if(!has_colors())       //确认终端是否支持彩色显示  
        {  
            endwin();  
            printf("can't support color \n");  
            return 0;  
        }  
      
  
        if(start_color() != OK)  //确认初始化彩色显示是否成功  
        {  
            endwin();  
            printf("can't initialize color \n");  
            return 0;  
        }  
          
  
        init_pair(3,COLOR_RED, COLOR_WHITE);  //设置颜色对前景红色，背景白色  
        attrset(COLOR_PAIR(3));               //使用刚才设置的颜色  
      
        for(i=0; i< 18; i+=2)                 //画横线和竖线  
        {  
                mvvline(9,2+i,'|',9);  
                mvvline(9,2+i+1,'_',9);  
        }        
  
        refresh();                           //刷新屏幕，以便显示内容  
        getch();                             //等待用户输入  
        sleep(2);                            //暂停两秒  
      
        endwin();                            //释放屏幕相关的资源  
      
        return 0;  
    }  
      
