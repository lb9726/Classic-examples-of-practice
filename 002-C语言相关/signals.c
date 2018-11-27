#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
#include<time.h>		 //for asctime() and time()
#include<ctype.h>    //for ispunct()
 
void function()
{
    int a = 3, b = 3, i ;
    for (i = 0; i < 3; i++)
    {
        a = a+b;
        printf("a = %d\n",a);
    }
}
//忽略ctrl +c 键的处理函数
void signHandler(int signNo)
{
    printf("singal:%d \n",signNo);
    char arr[40];
    printf("如果想安全退出服务器请按输入 exit\n");
    printf("请输入指令: ");
    scanf("%s",arr);
    if (0 == strcmp("exit",arr))
    {
        printf("结束\n");
        function();
        exit(0);
    }
}

int main()
{
    signal(SIGINT, signHandler);
    while(1)
    {
    ;
    }
    printf("fuck!\n");
}
