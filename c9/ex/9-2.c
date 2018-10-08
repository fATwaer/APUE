#include "apue.h"
#include <errno.h>
#include <sys/wait.h>
static void
pr_ids(const char *name)
{
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, sid = %ld, tpgrp = %ld\n",
           name, (long)getpid(), (long)getppid(), (long)getpgrp(), (long)getsid(getpid()),
           (long)tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int
main()
{
    pid_t pid;

    // sh is controlling process
    pr_ids("parent");
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        pr_ids("child");


        setsid();
        pr_ids("new pg");

        exit(0);
    }

    wait(NULL);
    exit(0);
}

