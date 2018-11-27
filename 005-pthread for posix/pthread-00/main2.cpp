//创建线程
//退出线程
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thrd_func(void *arg);
pthread_t tid;

int main()
{
    // 创建线程tid，且线程函数由thrd_func指向，是thrd_func的入口点，即马上执行此线程函数
    if (pthread_create(&tid,NULL,thrd_func,NULL)!=0)
    {
        printf("Create thread error!\n");
        exit(1);
    }

    printf("TID in pthread_create function: %u.\n",tid);
    printf("Main process: PID: %d,TID: %u.\n",getpid(),pthread_self());

    sleep(1); //race

    return 0;
}

void *thrd_func(void *arg)
{
    printf("I am new thread!\n");
    printf("New process:  PID: %d,TID: %u.\n",getpid(),pthread_self());
    printf("New process:  PID: %d,TID: %u.\n",getpid(),tid);

    pthread_exit(NULL); //退出线程
//    return ((void *)0);
}
