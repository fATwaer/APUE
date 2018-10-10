#include "apue.h"
#include <stdio.h>
#include <fcntl.h>

struct out{
    int a[10];
    int b;
    char c[32];
};

int
main()
{
    int n;
    int fd;
    int m;
    struct out a, b;
    FILE *fp;

    memmove(a.c, "string..", 32);
    a.b = 1024;

    n = 100;

    if ((fd = open("temp.file", O_RDWR|O_CREAT|O_TRUNC , 0644)) < 0)
        err_sys("open error");
    if (write(fd, &a, sizeof(a)) != sizeof(a))
        err_sys("write error");

    if (read(fd, &b, sizeof(a)) < 0)
        err_sys("read error");

    printf("str = %s, var = %d\n", b.c, b.b);

    close(fd);

    if ((fp = fopen("temp.file", "r+")) == NULL)
        err_sys("fopen error");
    if ((fread(&b, sizeof(a), 1, fp)) != 1)
        err_sys("fread error");

    printf("str = %s, var = %d\n", b.c, b.b);
    
    fclose(fp);
    exit(0);

}

