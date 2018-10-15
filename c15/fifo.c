#include <sys/stat.h>
#include <stdio.h>
#include "apue.h"
#include <fcntl.h>
#include <dirent.h>

int 
main()
{
    int fd;
    DIR *dp;
     
    if ((dp = opendir(".")) == NULL)
        err_sys("opendir error");
    fd = dirfd(dp);
    if (mkfifoat(fd, "fifo", O_RDONLY|O_CREAT|O_TRUNC) < 0)
        err_sys("mkfifo error");
}
