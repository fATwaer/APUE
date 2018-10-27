#include <stdio.h>
#include <fcntl.h>
#include "apue.h"
extern int serv_listen(const char *name);
extern int serv_accept(int listenfd, uid_t *uidptr);
extern int send_fd(int, int);
int 
main()
{
    int sfd;
    uid_t uid;
    int fd;

    fd = open("server.file", O_CREAT|O_RDWR|O_TRUNC, 0666);

    while (1) {
        sfd = serv_listen("UNIX.socket");
        printf("listen fd = %d\n", sfd);
        sfd = serv_accept(sfd, &uid);
        printf("accept connect, uid = %d, accept fd = %d\n", uid, sfd);
        dup2(fd, 30);       
        if (send_fd(sfd, 30) < 0)
            printf("send error");
        close(sfd);
    }

}

