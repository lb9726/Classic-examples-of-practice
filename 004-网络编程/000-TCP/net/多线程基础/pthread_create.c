#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

void *function(void *arg);
struct ARG
{
    int connfd;
    int other;
};

int main()
{
    struct ARG arg;
    int connfd, sockfd;
    pthread_t tid;
    .....
    while(1)
    {
        if (-1 == (connfd = accept(sockfd, NULL ,NULL)))
        {
            // handle exception
        }
        arg.connfd  = connfd;
        if (pthread_create(&tid, NULL , function, (void *)arg))
        {
            // handle exception
        }
    }
}

void *function(void *arg)
{
    struct ARG info;
    info.connfd = ((struct ARG *)arg)->connfd;
    info.other = ((struct ARG *)arg)->other;
    ....
    close(info.connfd);
    pthread_exit(NULL);
}