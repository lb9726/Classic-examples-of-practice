#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QProcess>
#include "LcdCommon.h"
#include "LcdClient.h"

static int running = 1; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void signal_proc(int signal)
{
    printf("\nSignal %d\n", signal);

    running = 0;

    qApp->exit(signal);

    return;
}

void *lcd_proc_line1(void *data)
{
    while(running)
    {
        pthread_mutex_lock(&mutex);
        pthread_mutex_unlock(&mutex);
        usleep(250 * 1000); // 250ms
    }

    printf("thread lcd_proc_line1 exit\n");

    return data;
}

void *lcd_proc_line2(void *data)
{
    QTcpSocket client;

    client.connectToHost(QHostAddress::LocalHost, LCD_SERVER_PORT);
    if (!client.waitForConnected(1000)) { // 1s
        qWarning()<<"client.connectToHost Error!";
    }

    while(running)
    {
        if (client.state() == QAbstractSocket::ConnectedState) {
            client.waitForReadyRead(1000); // 1s
            qint64 nlen =  client.bytesAvailable();
            if (nlen >= LCD_MSG_LENGTH) {
                QByteArray msg = client.readAll();
                qDebug()<<"data:"<<msg.trimmed();
                pthread_mutex_lock(&mutex);
                pthread_mutex_unlock(&mutex);
            }
        } else {
            usleep(250 * 1000); // 250ms
        }
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

    pthread_create(&tid1, NULL, lcd_proc_line1, NULL);
    pthread_create(&tid2, NULL, lcd_proc_line2, NULL);

    int ret = app.exec();

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    if (ret == SIGUSR2) {
        ret = QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }

    return ret;
}
