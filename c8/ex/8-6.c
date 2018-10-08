#include "apue.h"
#include <stdio.h>

int
main()
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        exit(0);
    
    sleep(4);
    system("ps -l");

    exit(0);
}
