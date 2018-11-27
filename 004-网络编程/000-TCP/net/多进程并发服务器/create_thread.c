#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
    pid_t pid;
    int status;
    if (0 == (pid = vfork()))
    {
        sleep(2);
        printf("child running .\n");
        printf("child sleeping .\n");
        sleep(5);
        printf("child dead.\n");
        exit(0);
    }
    else if (pid > 0)
    {
        printf("parent runing .\n");
        printf("parent exit\n");
        exit(0);
    }
    else 
    {
        printf("fork error.\n");
        exit(0);
    }
}
