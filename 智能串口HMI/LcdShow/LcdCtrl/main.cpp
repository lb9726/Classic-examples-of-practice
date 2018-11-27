#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <QCoreApplication>
#include <QProcess>
#include "LcdCommon.h"
#include "LcdCtrl.h"

static int running = 1;
static int pausing = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void signal_proc(int signal)
{
    printf("\nSignal %d\n", signal);
    running = 0;
    qApp->exit(signal);
}

void *lcd_proc_line1(void *data)
{
    int  nlen = 0;
    char buf[LCD_MSG_LENGTH];

    while(running)
    {
        pausing = 0;
        int devid = machine_init();

        if (devid > 0) {
            memset(buf, LCD_MSG_STRING_END, LCD_MSG_LENGTH);
            nlen = read(devid, buf, LCD_MSG_LENGTH - 1);
        }

        if (nlen == 0) {
            pausing = 1;
        }

        if (!pausing) {
            pthread_mutex_lock(&mutex);
            cmd_parse(buf, nlen);
            pthread_mutex_unlock(&mutex);
        } else {
            machine_exit();
        }

        usleep(500 * 1000); // 500ms
    }

    printf("thread lcd_proc_line1 exit\n");

    return data;
}

void *lcd_proc_line2(void *data)
{
    while(running)
    {
        if (!pausing) {
            pthread_mutex_lock(&mutex);
            cmd_run();
            pthread_mutex_unlock(&mutex);
        }

        usleep(500 * 1000); // 500ms
    }

    printf("thread lcd_proc_line2 exit\n");

    return data;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    pthread_t tid1, tid2;

    struct sigaction signalact;
    signalact.sa_handler = signal_proc;
    sigemptyset(&signalact.sa_mask);
    signalact.sa_flags = 0;
    sigaction(SIGHUP,  &signalact, NULL);
    sigaction(SIGINT,  &signalact, NULL);
    sigaction(SIGQUIT, &signalact, NULL);
    sigaction(SIGUSR1, &signalact, NULL); // For Stop
    sigaction(SIGUSR2, &signalact, NULL); // For Upgrade & Restart

    machine_init();

    pthread_create(&tid1, NULL, lcd_proc_line1, NULL);
    pthread_create(&tid2, NULL, lcd_proc_line2, NULL);

    int ret = app.exec();

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    machine_exit();

    if (ret == SIGUSR2) {
        ret = QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }

    return ret;
}
