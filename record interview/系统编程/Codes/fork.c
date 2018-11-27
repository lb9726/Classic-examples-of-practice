#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

void print_exit();

void print_exit()
{
    printf("the exit pid:%d\n", getpid());
}

int main()
{
    pid_t pid;
    atexit(print_exit); // 注册该进程退出时的回调函数
    pid = fork();
    if (pid < 0)
    {
        printf("error in fork!");
    }
    else if (pid == 0)
    {
        printf("I am the child process,my process is %d \n", getpid());
    }
    else 
    {
        printf("I am the parent process,my process id is %d\n", getpid());
        sleep(2);
        wait();
    }
}
/*
一次运行的结果:
I am the parent process,my process id is 4558
I am the child process,my process is 4559 
the exit pid:4559
the exit pid:4558
*/
