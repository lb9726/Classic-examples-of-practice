
#include <pthread.h>
#include <stdio.h>


int sum =0;

void *runner(void *p);

int main(int argc, char *argv[]){

	pthread_t tid;
	pthread_attr_t attr;
	char *c;
	c="hello";
	pthread_attr_init(&attr);
	pthread_create(&tid,NULL,runner,NULL);
	pthread_join(tid,NULL);

	printf("%s\n",c);

}

void *runner(void *p){
	printf("Ahoj");
	
	pthread_exit(0);
}