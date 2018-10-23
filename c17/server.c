#include <stdio.h>
#include "apue.h"

extern int serv_listen(const char *name);

extern int serv_accept(int listenfd, uid_t *uidptr);

int 
main()
{
    int fd;
    uid_t uid;

    fd = serv_listen("UNIX.socket");
    printf("listen fd = %d\n", fd);
    fd = serv_accept(fd, &uid);
    printf("accept fd = %d\n", fd);

    printf("accept connect, uid = %d\n", uid);
}
