/*

*/

#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<semaphore.h>
#define N 2            //消费者或生产者的数目
#define M 10           //缓冲数目
int in = 0 ;           //生产者放置产品的位置
int out = 0 ;          //消费者取产品的位置
int buff[M]={0};       //缓冲初始化为0,开始时没有产品
sem_t empty_sem;       //同步信号量,当满了时阻止生产者放产品
sem_t full_sem;        //同步信号量,当没有产品时阻止消费者消费
pthread_mutex_t mutex; //互斥信号量,一次只有一个线程访问缓冲
int product_id = 0;    //生产者id
int prochase_id = 0;   //消费者id

//打印缓冲情况
void print()
{
	int i;
	for(i=0;i<M;i++)
		printf("%d",buff[i]);
	printf("\n");
}

//生产者方法
void *produce()
{
	int id=++product_id;
	while(1)
	{
		sleep(1);//
		sem_wait(&empty_sem); // P操作 P操作(申请资源)
		pthread_mutex_lock(&mutex);
		in = in%M;
		printf("product%d in %d like:\t", id, in);
		buff[in] = 1;
		print();
		++in;
		pthread_mutex_unlock(&mutex);
		sem_post(&full_sem); // V操作 V操作(释放资源)
	}
}

//消费者方法
void *prochase()
{
	int id= ++prochase_id;
	while(1)
	{
		//用sleep(1)的的数量可以调节生产和消费的速度,便于观察
		sleep(1);
		sem_wait(&full_sem);
		pthread_mutex_lock(&mutex);
		out =out%M;
		printf("prochase%d in %d.like:\t", id, out);
		
		buff[out] = 0;
		print();
		++out;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty_sem);
	}
}
    
int main()
{
	pthread_t id1[N];
	pthread_t id2[N];
	int i;
	int ret[N];

//初始化同步信号量
	int ini1 = sem_init(&empty_sem, 0, M);
	int ini2 = sem_init(&full_sem, 0, 0);
	if(ini1 && ini2 != 0)
	{
		printf("sem init failed\n");
		exit(1);
	}
//初始化互斥信号量
    int ini3 = pthread_mutex_init(&mutex, NULL);
    if(ini3 != 0)
    {
    	printf("mutex init failed\n");
    	exit(1);
    }
    //创建N个生产者线程
    for(i = 0; i < N; i++)
    {
    	ret[i] = pthread_create(&id1[i], NULL, produce, (void *)(&i));
    	if(ret[i] < 0) 
    	{
    		printf("product %d creation failed\n", i);
    		exit(1);
    	}
    	printf("创建N个生产者线程!\n");
    }
    //创建N个消费者线程
    for(i = 0; i < N; i++)
    {
    	ret[i] = pthread_create(&id2[i], NULL, prochase, NULL);
    	if(ret[i] < 0)
    	{
    		printf("prochase %d creation failed\n", i);
    		exit(1);
    	}
    	printf("创建N个消费者线程!\n");
    }
    printf("创建N个生产者线程，创建N个消费者线程结束!\n");
    //销毁进程
    for(i = 0; i < N; i++)
    {
    	pthread_join(id1[i], NULL);
    	pthread_join(id2[i], NULL);
    	printf("enter destory!\n");
    }
    exit(0);
}    
    
/*
P(S) 含义如下:
if (信号量的值大于0)
{
	申请资源的任务继续运行;
	信号量的值减一;
}
else 
{ 
	申请资源的任务阻塞;
}

V(S) 含义如下:
if (没有任务在等待该资源) 
{ 
	信号量的值加一;
}
else 
{ 
	唤醒第一个等待的任务,让其继续运行
}
*/

/*
这两个函数都要用一个由sem_init调用初始化的信号量对象的指针做参数。
 sem_post函数的作用是给信号量的值加上一个“1”，它是一个“原子操作”－－－即同时对同一个信号量做加“1”操作的两个线程是不会冲突的；而同时对同一个文件进行读、加和写操作的两个程序就有可能会引起冲突。信号量的值永远会正确地加一个“2”－－因为有两个线程试图改变它。
 sem_wait函数也是一个原子操作，它的作用是从信号量的值减去一个“1”，但它永远会先等待该信号量为一个非零值才开始做减法。也就是说，如果你对一个值为2的信号量调用sem_wait(),线程将会继续执行，介信号量的值将减到1。如果对一个值为0的信号量调用sem_wait()，这个函数就会地等待直到有其它线程增加了这个值使它不再是0为止。如果有两个线程都在sem_wait()中等待同一个信号量变成非零值，那么当它被第三个线程增加一个“1”时，等待线程中只有一个能够对信号量做减法并继续执行，另一个还将处于等待状态。
 信号量这种“只用一个函数就能原子化地测试和设置”的能力下正是它的价值所在。还有另外一个信号量函数sem_trywait，它是sem_wait的非阻塞搭档。

 最后一个信号量函数是sem_destroy。这个函数的作用是在我们用完信号量对它进行清理。下面的定义：
 #include<semaphore.h>
 int sem_destroy (sem_t *sem);
 这个函数也使用一个信号量指针做参数，归还自己战胜的一切资源。在清理信号量的时候如果还有线程在等待它，用户就会收到一个错误。
 与其它的函数一样，这些函数在成功时都返回“0”。
*/
/*
创建N个生产者线程!
创建N个生产者线程!
创建N个消费者线程!
创建N个消费者线程!
创建N个生产者线程，创建N个消费者线程结束!
product1 in 0 like:	1000000000
product2 in 1 like:	1100000000
prochase2 in 0.like:	0100000000
prochase1 in 1.like:	0000000000
product2 in 2 like:	0010000000
product1 in 3 like:	0011000000
prochase1 in 2.like:	0001000000
prochase2 in 3.like:	0000000000
product1 in 4 like:	0000100000
prochase1 in 4.like:	0000000000
product2 in 5 like:	0000010000
prochase2 in 5.like:	0000000000
product1 in 6 like:	0000001000
product2 in 7 like:	0000001100
prochase2 in 6.like:	0000000100
prochase1 in 7.like:	0000000000
product2 in 8 like:	0000000010
product1 in 9 like:	0000000011
prochase1 in 8.like:	0000000001
prochase2 in 9.like:	0000000000
product2 in 0 like:	1000000000
product1 in 1 like:	1100000000
prochase1 in 0.like:	0100000000
prochase2 in 1.like:	0000000000
product1 in 2 like:	0010000000
product2 in 3 like:	0011000000
prochase1 in 2.like:	0001000000
prochase2 in 3.like:	0000000000
product1 in 4 like:	0000100000
prochase1 in 4.like:	0000000000
product2 in 5 like:	0000010000
prochase2 in 5.like:	0000000000
product1 in 6 like:	0000001000
product2 in 7 like:	0000001100
prochase2 in 6.like:	0000000100
prochase1 in 7.like:	0000000000
product2 in 8 like:	0000000010
prochase1 in 8.like:	0000000000
product1 in 9 like:	0000000001
prochase2 in 9.like:	0000000000

*/








