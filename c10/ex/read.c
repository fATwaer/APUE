#include "apue.h"
#include <stdio.h>
#include <fcntl.h>

int
main()
{
    int n;
    int fd;
    int m;

    n = 100;
    if ((fd = open("temp.file", O_RDWR|O_CREAT), 0644) < 0)
        err_sys("open error");
    if (write(fd, &n, sizeof(int)) != sizeof(int))
        err_sys("write error");

    if (read(fd, &m, sizeof(int)) < 0)
        err_sys("read error");

    printf("read() %d\n ", m);
}
