#include "apue.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <time.h>

#define STALE 30


int
serv_accept(int listenfd, uid_t *uidptr)
{
    int                 clifd, err, rval;
    socklen_t           len;
    time_t              staletime;
    struct sockaddr_un  un;
    struct stat         statbuf;
    char                *name;

    /*name space*/
    if ((name = malloc(sizeof(un.sun_path) + 1)) == NULL)
        return (-1);
    len = sizeof(un);
    if ((clifd = accept(listenfd, (struct sockaddr *)&un, &len)) < 0) {
        free(name);
        return (-2);
    }

    len -= offsetof(struct sockaddr_un, sun_path);
    memcpy(name, un.sun_path, len);
    name[len] = 0;
    if (stat(name, &statbuf) < 0) {
        rval = -3;
        goto errout;
    }

    if (S_ISSOCK(statbuf.st_mode) == 0) {
        rval = -4;
        goto errout;
    }

    if ((statbuf.st_mode & (S_IRWXG | S_IRWXO)) ||
        ((statbuf.st_mode &S_IRWXU) != S_IRWXU)) {
        rval = -5;
        goto errout;
    }

    staletime = time(NULL) - STALE;
    if (statbuf.st_atime < staletime ||
        statbuf.st_ctime < staletime ||
        statbuf.st_mtime < staletime) {
            rval = -6;
            goto errout;
    }

    if (uidptr != NULL)
        *uidptr = statbuf.st_uid;
    unlink(name);
    free(name);
    return (clifd);
errout:
    err = errno;
    close(clifd);
    free(name);
    errno = err;
    return (rval);
}

