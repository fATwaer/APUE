#include "apue.h"
#include <sys/socket.h>

/* control buffer size*/
#define CONTROLLEN CMSG_LEN(sizeof(int))


static struct cmsghdr *cmptr = NULL;


/** receive a file descriptor form a server process.
 *  and data is passed to `userfunc`.
 * return the received fd if success, else return -1;
 *
 */

int
recv_fd(int fd, ssize_t (*userfunc)(int, const void *, size_t))
{
    int         newfd, nr, status;
    char        *ptr;
    char        buf[MAXLINE];
    struct iovec iov[1];
    struct msghdr msg;

    status = -1;
    for (;;) {
        iov[0].iov_base = buf;
        iov[0].iov_len = sizeof(buf);
        msg.msg_iov = iov;
        msg.msg_iovlen = 1;
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        if (cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)
            return (-1);
        msg.msg_control = cmptr;
        msg.msg_controllen = CONTROLLEN;
        if ((nr = recvmsg(fd, &msg, 0)) < 0) {      // recvmsg() returns the received data length.
            struct stat statbuf;
            fstat(fd, &statbuf);
            printf("socket ? %s\n", S_ISSOCK(statbuf.st_mode)?"yes":"no");
            err_ret("recvmsg error");
            return (-1);
        } else if (nr == 0) {
            err_ret("connection closed by server");
            return (-1);
        }

        for (ptr = buf; ptr < &buf[nr];) {              // buf[0] == NULL and buf[1] == status
            if (*ptr++ == 0) {
                if (ptr != &buf[nr-1])
                    err_dump("message format error");
                status = *ptr & 0xFF;
                if (status == 0) {
                    if (msg.msg_controllen < CONTROLLEN)
                        err_dump("status = 0 but no fd");
                    newfd = *(int *)CMSG_DATA(cmptr);
                } else {
                    newfd = -status;
                }
                nr -= 2;
            }
        }
        if (nr > 0 && (*userfunc)(STDERR_FILENO, buf, nr) != nr)
            return (-1);
        if (status >= 0)
            return (newfd);

    }
}



