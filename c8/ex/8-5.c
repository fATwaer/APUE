#include "apue.h"
#include <sys/wait.h>

int 
main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        if (execlp("interp.file", "execarg", "execarg2", (char *)0) < 0)
            err_sys("exec error");
    if (waitpid(pid, NULL, 0) < 0)
        err_sys("waitpid error");
    exit(0);
}
