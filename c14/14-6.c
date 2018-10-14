#include "apue.h"
#include <string.h>
#include <fcntl.h>
#include <sys/uio.h>

#define N 3

int
main(int argc, char *argv[])
{
    char buf[2*N][20];
    struct iovec  vec[N];
    int i, n, fd;

    if ((fd = open(argv[1], O_RDWR)) < 0)
        err_sys("open error");

    for (i = 0; i < N; i++)
    {
        vec[i].iov_base = buf[2*i+1];
        vec[i].iov_len = 19;
        printf("sizeof: %d\n", sizeof(buf[2*i+1]));
    
    }

    if ((n = readv(fd, vec, N)) < 0)
        err_sys("readv error");

    for (i = 0; i < N; i++)
        printf("%s\n", buf[2*i+1]);
    fd = open(argv[2], O_RDONLY);
    read(fd, buf[0], 20);
    printf("buf=%s\n", buf[0]); 
}
