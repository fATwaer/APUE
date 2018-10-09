#include "apue.h"
#include <errno.h>
#include <sys/wait.h>

static void
handler(int signo)
{
    printf("SIGCHILD received\n");
    for (;;);
}


int
main()
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        exit(0);
    }

    sleep(2);
    wait(NULL);
    pause();
    exit(0);
}



