#include "apue.h"
#include <sys/wait.h>

static void
charatatime(char *str)
{
    char *ptr;
    int c;


    setbuf(stdout, NULL);
    for (ptr = str; (c = *ptr++) != 0; )
        putc(c, stdout);
}


int
main(void)
{
    pid_t pid;

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    }
    else if (pid == 0) {
        WAIT_PARENT();
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
        TELL_CHILD(pid);
    }

    exit(0);
}
