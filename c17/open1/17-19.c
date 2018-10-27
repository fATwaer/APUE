#include "open.h"
#include <sys/uio.h>



/**
 *  open the file by sedning the "name" and "oflag" to
 *  the connection server and reading a file desriptor back.
 *
 */

int
csopen(char *name, int oflag)
{
    pid_t           pid;
    int             len;
    char            buf[10];
    struct iovec    iov[3];
    static int      fd[2] = {-1, -1};

    if (fd[0] < 0) {
        if (fd_pipe(fd) < 0) {
            err_ret("fd_pipe error");
            return (-1);
        }
        if ((pid = fork()) < 0) {
            err_ret("fork error");
            return (-1);
        } else if (pid == 0) {
            close(fd[0]);           //child
            if (fd[1] != STDIN_FILENO &&
                dup2(fd[1], STDIN_FILENO) != STDIN_FILENO)
                    err_sys("dup2 error to stdin");
            if (fd[1] != STDOUT_FILENO &&
                dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
                    err_sys("dup2 error to stdout");
            if (execl("./opend", "opend", (char *)0) < 0)
                err_sys("execl error");
        }
        close(fd[1]);               //parent
    }
    sprintf(buf, " %d", oflag);
    iov[0].iov_base = CL_OPEN " ";
    iov[0].iov_len = strlen(CL_OPEN) + 1;
    iov[1].iov_base = name;
    iov[1].iov_len = strlen(name);
    iov[2].iov_base = buf;
    iov[2].iov_len = strlen(buf) + 1;
    len = iov[0].iov_len + iov[1].iov_len + iov[2].iov_len;
    if (writev(fd[0], &iov[0], 3) != len) {
        err_ret("write error");
        return (-1);
    }

    return (recv_fd(fd[0], write));
}
