#include "apue.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define QLEN       10

int
serv_listen(const char *name)
{
    struct sockaddr_un un;
    int                fd, len, err, rval;

    if (strlen(name) >= sizeof(un.sun_path)) {
        errno = ENAMETOOLONG;
        return (-1);
    }

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        return (-2);

    unlink(name); // exist

    memset(&un, 0, sizeof(un));
    un.sun_family= AF_UNIX;
    strcpy(un.sun_path, name);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(name);


    if (bind(fd, (struct sockaddr *)&un, len) < 0) {
        rval = -3;
        goto errout;
    }

    if (listen(fd, QLEN) < 0) {
        rval = -4;
        goto errout;
    }
    return (fd);

errout:
    err = errno;
    close(fd);
    errno = err;
    return (rval);
}

