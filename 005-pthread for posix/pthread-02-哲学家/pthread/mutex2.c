#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t mutex;
int counter;
void *doSomething(){


pthread_mutex_lock(&mutex);
int j;
counter += 1;
printf("Is started tid \n");

for(j=0; j<(0xFFFFFFF);j++);

printf("Its finished tid  \n");

pthread_mutex_unlock(&mutex);


return NULL;
}

int main(void){

pthread_t tid;
pthread_t tid2;

int i=0;


 if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
pthread_create(&tid, NULL, &doSomething, NULL);
	
pthread_create(&tid2, NULL, &doSomething, NULL);





pthread_join(tid,NULL);
pthread_join(tid2,NULL);

pthread_mutex_destroy(&mutex);

}