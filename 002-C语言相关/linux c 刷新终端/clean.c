#include <stdio.h>  
#include <unistd.h>  
  
int main(void)  
{  
    int i = 0;  
    while(1){  
        printf("%d\n", i);  
        printf("\033[1A"); //先回到上一行  
        printf("\033[K");  //清除该行  
        i++;  
        sleep(1);  
    }  
    return 0;  
}  

/*
      详细请看：http://phpman.cn/2012/12/15/linux-c-%E5%88%B7%E6%96%B0%E7%BB%88%E7%AB%AF%E5%B1%8F%E5%B9%95%E7%9A%84%E6%96%B9%E6%B3%95/
       当我们希望在终端中的某一行显示进度或者显示动态的时间，这个时候我们就需要刷新终端屏幕了，即是在同一个位置显示不同的内容。当然这里是个简单的应用，以后可以更复杂。
       下面这段代码，可以在一行中每隔一秒显示以下数字。
       
             以下简单的说明： 
              \e[ 或 \033[ 是 CSI，用来操作屏幕的。
              \e[K 表示从光标当前位置起删除到 EOL （行尾）
              \e[NX 表示将光标往X方向移动N，X = A(上) / B(下) / C(左) / D(右)，\e[1A 就是把光标向上移动1行

      这样就可以实现简单的刷新终端的功能了。当然在windows下有graphics.h头文件，在linux下有curses.h 来操作终端屏幕。以后学习了。

*/
