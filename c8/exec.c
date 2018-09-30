#include "apue.h"
#include <sys/wait.h>

char *env_init[] ={"USER=unknown", "PATH=/home/moonlight/apue/c8", NULL};

int
main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    }
    else if (pid == 0) {
        if (execle("/home/moonlight/apue/c8/echoall", "echoall",
                   "myarg1", "My argv2", (char *)0, env_init) < 0)
                    err_sys("execle error");
        exit(0);
    }

    wait(NULL);
    char buf[] = "\n\n\n\n";
    write(STDOUT_FILENO, buf, 4);
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    }
    else if (pid == 0) {
        if (execlp("echoall", "echoall",
                   "arg1", (char *)0) < 0)
                    err_sys("execle error");
    }

    exit(0);
}
