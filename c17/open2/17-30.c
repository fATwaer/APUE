#include "opend.h"
#include <poll.h>
#include <syslog.h>

#define NALLOC 10


static struct pollfd *
grow_pollfd(struct pollfd *pfd, int *maxfd)
{
    int         i;
    int         oldmax = *maxfd;
    int         newmax = oldmax + NALLOC;

    if ((pfd = realloc(pfd, newmax * sizeof(struct pollfd))) == NULL)
        err_sys("realloc error");
    for (i = oldmax; i < newmax; i++) {
        pfd[i].fd = -1;
        pfd[i].events = POLLIN;
        pfd[i].revents = 0;
    }
    *maxfd = newmax;
    return (pfd);
}

void
loop(void)
{
    int         i, listenfd, clifd, nread;
    char        buf[MAXLINE];
    uid_t       uid;
    struct pollfd *pollfd;
    int         numfd = 1;
    int         maxfd = NALLOC;

    //init
    if ((pollfd = malloc(NALLOC * sizeof(struct pollfd))) == NULL)
        err_sys("malloc error");
    for (i = 0; i < NALLOC; i++) {
        pollfd[i].fd = -1;
        pollfd[i].events = POLLIN;
        pollfd[i].revents = 0;
    }

    if ((listenfd = serv_listen(CS_OPEN)) < 0)
        syslog(3, "serv_listen error");
    client_add(listenfd, 0);
    pollfd[0].fd = listenfd;

    for (;;) {
        if (poll(pollfd, numfd, -1) < 0)
            syslog(3, "poll error");

        if (pollfd[0].revents & POLLIN) {
            if ((clifd = serv_accept(listenfd, &uid)) < 0)
                syslog(3, "poll error");
            client_add(clifd, uid);
        
            // connection established
            if (numfd == maxfd)
                pollfd = grow_pollfd(pollfd, &maxfd);
            pollfd[numfd].fd = clifd;
            pollfd[numfd].events = POLLIN;
            pollfd[numfd].revents = 0;
            numfd++;
            syslog(3, "new connection : %d, fd %d", uid, clifd);
        }

        for (i = 1; i < numfd; i++) {
            if (pollfd[i].revents & POLLHUP)
                goto hungup;
            else if (pollfd[i].revents & POLLIN) {
                if ((nread = read(pollfd[i].fd, buf, MAXLINE)) < 0)
                    syslog(3, "read error on fd %d", pollfd[i].fd);
                else if (nread == 0) {
hungup:
                    syslog(3, "connection closed");
                    close(pollfd[i].fd);
                    if (i < numfd - 1) {
                        pollfd[i].fd = pollfd[numfd-1].fd;
                        pollfd[i].events = pollfd[numfd-1].events;
                        pollfd[i].revents = pollfd[numfd-1].events;
                        i--;
                    }
                    numfd--;
                } else {
                    handle_request(buf, nread, pollfd[i].fd, client[i].uid);
                }
            }
        }

    }

}

