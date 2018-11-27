#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>    // zero()
#include <stdlib.h>     // exit()
#include <time.h>       // ctime()
#include <string.h>     //strlen

#define MAXFD 64
#define MAXLINE 255

void daemon_init(const char *pname, int facility)
{
    int i ;
    pid_t pid;
    if (0 != (pid = fork()))  /*创建第一个子进程*/
    {
        exit(0); /*终止父进程*/
    }
    /*第一个子进程继续*/
    setsid();    /*成为会话头*/
    signal(SIGHUP, SIG_IGN); /*忽略SIGHUP信号*/
    if (0 != (pid = fork()))
    {
        exit(0); /*第一个子进程终止*/
    }
    /*第二个子进程继续*/

    chdir("/"); /*改变工作目录*/
    umask(0); /*清除文件模式创建掩码，使新文件的权限位不受原先文件模式创建掩码的权限位的影响*/

    for(i = 0; i < MAXFD; ++i) /*关闭所有打开的文件描述字*/
    {
        close(i);
    }
    openlog(pname, LOG_PID, facility); /* 用syslogd处理错误 */
}

int main(int argc, char *argv[])
{
    int listenfd;
    int connfd;
    socklen_t addrlen;
    socklen_t len;
    struct sockaddr cliaddr;
    struct sockaddr_in server;
    char buff[MAXLINE];
    time_t ticks;
    bzero(&server, sizeof(server));
    bzero(&cliaddr, sizeof(cliaddr));
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    daemon_init(argv[0], 0);

    if (-1 == (listenfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        syslog(LOG_NOTICE | LOG_LOCAL0, "socket error");
        exit(-1);
    }

    if (-1 == bind(listenfd, (struct sockaddr*)&server, sizeof(struct sockaddr)))
    {
        syslog(LOG_NOTICE | LOG_LOCAL0, "bind() socket error");
        exit(-1);
    }

    if (-1 == listen(listenfd, 5))
    {
        exit(1);
    }

    for (; ;)
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, &cliaddr, &len);
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        int a;
        if (-1 == (a = write(connfd, buff, strlen(buff))))
        {
            syslog(LOG_NOTICE|LOG_LOCAL0, "write error");
            exit(0);
        }
        close(connfd);
    }
}
