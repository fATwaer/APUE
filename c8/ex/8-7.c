#include "apue.h"
#include <dirent.h>
#include <fcntl.h>
#include <sys/wait.h>
int
main()
{
    DIR *dp;
    int fd;
    pid_t pid;


    if ((dp = opendir("/")) == NULL)
        err_sys("open dir failed");

    fd = dirfd(dp);
    printf("fd = %d\n", fd);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        printf("fd: %d, fd_cloexec flag %s\n", fd, fcntl(fd, F_GETFD) == FD_CLOEXEC ?
               "on" : "off");
        printf("exec ...\n");
        execl("/home/moonlight/apue/c8/ex/newprocess", "newprocess", (char *)0);
        err_sys("exec error");
    }


    if (waitpid(pid, NULL, 0) == 0)
        err_sys("waitpid error");

    printf("child terminates\n");

    exit(0);
}



