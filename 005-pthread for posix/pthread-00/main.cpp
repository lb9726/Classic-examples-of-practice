//获取线程ID
//比较线程ID是否相等
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{
    pthread_t thread_id;

    thread_id=pthread_self(); // 返回调用线程的线程ID
    printf("Thread ID: %lu.\n",thread_id);

    if (pthread_equal(thread_id,pthread_self()))
    {
        printf("Equal!\n");
    }
    else
    {
        printf("Not equal!\n");
    }
    return 0;
}
