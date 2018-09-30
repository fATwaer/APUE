#include "apue.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void
pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n",
               WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal numer = %d%s\n",
               WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? " (core file generagted) " : "");
#else
                "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stoped ,sighed number = %d\n",
               WSTOPSIG(status));
}

int
mysystem(const char *cmdstring)
{
    pid_t pid;
    int status;

    if (cmdstring == NULL)
        return 1;
    if ((pid = fork()) < 0)
        status = -1;
    else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127);
    } else {
        while (waitpid(pid, &status, 0) < 0)
            if (errno != EINTR) {
                status = -1;
                break;
            }    
    }
    
    return (status) ;
}



int
main(int argc, char *argv[])
{
    int status;
    
    if (argc < 2)
        err_quit("command-line argument required");

    if ((status = mysystem(argv[1])) < 0)
        err_sys("system() execute error");
    pr_exit(status);
}
