#include "apue.h"

int globvar = 6;


int
main(int argc, char *argv[])
{
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork\n");
    if ((pid = vfork()) < 0)
        err_sys("vfork error");
    else if (pid == 0) {
        globvar++;
        var++;
        fclose(stdout);
        exit(0);
    }
    //waitpid(pid, NULL, 0);
    /* parent */
    int i;
    char buf[10];

    i = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    sprintf(buf, "%d\n", i);
    write(STDOUT_FILENO, buf, 2);
    exit(0);
}

