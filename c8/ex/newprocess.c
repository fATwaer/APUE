#include "apue.h"
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    DIR *dp;
    //directly print fd_cloexec flag 
    printf("fd: %d, fd_cloexec flag %s\n", 3,
            fcntl(3, F_GETFD) == FD_CLOEXEC ? "on": "off");
   
    //by fdopendir to judge the fd is a bad descriptor or not.
    if (fdopendir(3) == NULL)
        printf("fdopendir failed\n");
   
    //reopen the directory .
    if ((dp = opendir("/")) == NULL)
        err_sys("opendir error");
    printf("fd: %d, fd_cloexec flag %s\n", dirfd(dp),
            fcntl(dirfd(dp), F_GETFD) == FD_CLOEXEC ? "on": "off");
    exit(0);
}
