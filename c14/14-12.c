#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int             fd;
    pid_t           pid;
    char            buf[5];
    struct stat     statbuf;

    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
    }
    if ((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
        err_sys("open error");
    if (write(fd, "abcdef", 6) != 6)
        err_sys("write error");

    /** turn om set group id, turn off group execute*/
    if (fstat(fd, &statbuf) < 0)
        err_sys("stat error");
    if (fchmod(fd, (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        err_sys("fchmod error");

    TELL_WAIT();

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0) {
        /** write lock entire file*/
        if (write_lock(fd, 0, SEEK_SET, 0) < 0)
            err_sys("write lock error");

        TELL_CHILD(pid);

        if (waitpid(pid, NULL, 0) < 0)
            err_sys("waitpid error");
    } else {
        WAIT_PARENT();

        set_fl(fd, O_NONBLOCK);

        if (read_lock(fd, 0, SEEK_SET, 0) != -1)
            err_sys("child : read_lock succeeded");

        printf("read_lock of already_locked region returns %d\n", errno);

        /** try to read the mandatory locked file */
        if (lseek(fd, 0, SEEK_SET) == -1) /** both parent and child point to one file table, which shares same seek*/
            err_sys("seek error");
        if (read(fd, buf, 2) < 0)
            err_ret("read failed (mandatory locking works)");
        else
            printf("read OK(no mandatory locking), buf = %2.2s\n", buf);

    }

    exit(0);
}



