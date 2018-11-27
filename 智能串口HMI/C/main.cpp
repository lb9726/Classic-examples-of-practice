#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "LcdCommon.h"
#include "LcdCtrl.h"

static int running = 1; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void signal_proc(int signal)
{
    printf("\nSignal %d\n", signal);

    running = 0;

    return;
}

void *lcd_proc_line1(void *data)
{
    while(running)
    {
        char *buf = get_line1_data();
        printf("line1:%s\n", buf);
        pthread_mutex_lock(&mutex);
        line1_disp(buf);
        pthread_mutex_unlock(&mutex);
        usleep(500 * 1000); // 500ms
    }

    printf("thread lcd_proc_line1 exit\n");

    return data;
}

void *lcd_proc_line2(void *data)
{
    while(running)
    {
        char *buf = get_line2_data();
        printf("line2:%s\n", buf);
        pthread_mutex_lock(&mutex);
        line2_disp(buf);
        pthread_mutex_unlock(&mutex);
        usleep(1000 * 1000); // 1000ms
    }

    printf("thread lcd_proc_line2 exit\n");

    return data;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    pthread_t tid1, tid2;

#ifndef DEBUG
    ret = daemon(0, 0);
#endif

    struct sigaction signalact;
    signalact.sa_handler = signal_proc;
    sigemptyset(&signalact.sa_mask);
    signalact.sa_flags = 0;
    sigaction(SIGHUP,  &signalact, NULL);
    sigaction(SIGINT,  &signalact, NULL);
    sigaction(SIGQUIT, &signalact, NULL);
    sigaction(SIGUSR1, &signalact, NULL); // For Stop
    sigaction(SIGUSR2, &signalact, NULL); // For Upgrade & Restart

    if (machine_init() < 0) {
        printf("machine_init error!\n");
        machine_exit();
        return -1;
    }

    pthread_create(&tid1, NULL, lcd_proc_line1, NULL);
    pthread_create(&tid2, NULL, lcd_proc_line2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    machine_exit();

    return ret;
}
