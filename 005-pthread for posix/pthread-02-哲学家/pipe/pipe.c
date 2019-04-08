#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define READ_PIPE 0
#define WRITE_PIPE 1

int main(void)
{
    int     fd[2];
    pid_t   pid;
    char    string[] = "Hello, world!";
    char    readbuffer[80];

    pipe(fd);
    pid = fork();

    if (pid == -1)
    {
        printf("ERROR: Cannot make fork");
        exit(1);
    }

    if (pid == 0)
    {
        /* Child process closes up input side of pipe */
        close(fd[READ_PIPE]);
        /* Send "string" through the output side of pipe */
        write(fd[WRITE_PIPE], string, (strlen(string)+1));
        exit(0);
    }
    else
    {
        /* Parent process closes up output side of pipe */
        close(fd[WRITE_PIPE]);

        /* Read in a string from the pipe */
        read(fd[READ_PIPE], readbuffer, sizeof(readbuffer));
        printf("Received string: %s", readbuffer);
    }
    return(0);
}
