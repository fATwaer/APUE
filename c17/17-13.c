#include "apue.h"
#include <sys/socket.h>

#define CONTROLLEN CMSG_LEN(sizeof(int))

static struct cmsghdr *cmptr = NULL;

/*
 * pass a file decirptor to another process .
 * if fd < 0, then -fd is sent back instead
 * as the error status.
 */

int
send_fd(int fd, int fd_to_send)
{
    struct iovec  iov[1];
    struct msghdr msg;
    char          buf[2];

    iov[0].iov_base = buf;
    iov[0].iov_len = 2;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    if (fd_to_send < 0)  {
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        buf[1] = -fd_to_send;
        if (buf[1] == 0)
            buf[1] = 1;
    } else {
        if (cmptr == NULL && ((cmptr = malloc(CONTROLLEN)) == NULL))
            return (-1);
        cmptr->cmsg_level = SOL_SOCKET;
        cmptr->cmsg_type = SCM_RIGHTS;
        cmptr->cmsg_len = CONTROLLEN;
        msg.msg_control =cmptr;
        msg.msg_controllen = CONTROLLEN;
        *(int *)CMSG_DATA(cmptr) = fd_to_send;
        buf[1] = 0;     /* meaning status is OK*/


    }
    buf[1] = 0;
    if (sendmsg(fd, &msg, 0) != 2)  // sendmsg return the buffer bytes that
        return (-1);                //iov_base  pointer to

    return (0);
}
