#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define P_FILOZOFOV 5
#define P_FORK 5

pthread_mutex_t mutex_forks[P_FORK];
pthread_mutex_t m;
pthread_t filozofi[P_FILOZOFOV];

void *Filozofi(void *i)
{
    int id = *((int*)i);
    while (1)
    {
        pthread_mutex_lock(&m);
        printf("Filozofer %d prestal mysliet a chce jest\n",id);
        pthread_mutex_lock(&mutex_forks[id]);
        pthread_mutex_lock(&mutex_forks[(id+1)%5]);
        pthread_mutex_unlock(&m);

        printf("Filozofer %d papa s right_fork(%d) a left_fork(%d)\n",id,id,((id+1)%5));
        pthread_mutex_unlock(&mutex_forks[id]);
        pthread_mutex_unlock(&mutex_forks[(id+1)%5]);
        printf("Filozofer %d dopapal a poklada right_fork(%d) a left_fork(%d) \n",id,id,(id+1)%5);
        break;
    }
}

int main()
{
    int i, j;
    int id = 0;
    int N = 4;

    for (j = 0; j < 5; ++j)
    {
        pthread_create(&(filozofi[j]), NULL ,Filozofi,&j);
        printf("Filozof %d rozmysla \n", j);
        sleep(2);
    }

    for (i = 0; i < 5; ++i)
    {
        pthread_join(filozofi[i], NULL);
    }
    return 0;
}
