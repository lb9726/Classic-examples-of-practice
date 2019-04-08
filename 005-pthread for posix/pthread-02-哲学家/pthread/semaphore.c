#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>

sem_t sem;
int counter;
void *doSomething()
{
    sem_wait(&sem);
    int j;
    counter += 1;
    printf("Is started tid \n");

    for (j = 0; j < (0xFFFFFFF); ++j);

    printf("Its finished tid  \n");

    sem_post(&sem);

    return NULL;
}

int main(void)
{
    pthread_t tid;
    pthread_t tid2;
    pthread_t tid3;
    pthread_t tid4;

    sem_init(&sem, 0, 3);

    pthread_create(&tid, NULL, &doSomething, NULL);
    pthread_create(&tid2, NULL, &doSomething, NULL);
    pthread_create(&tid3, NULL, &doSomething, NULL);
    pthread_create(&tid4, NULL, &doSomething, NULL);

    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

}
