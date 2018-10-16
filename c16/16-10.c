#include "apue.h"
#include <sys/socket.h>

#define MAXSLEEP 128

int 
connect_retry(int domin, int type, int protocol
              const struct sockaddr *addr, socklen_t alen)
{
    int numsec, fd;

    // connect with exponetial backoff
    for (numsec = 1; numsec <= MAXSLEEP; numsec <<1) {
        if ((fd = socket(domain, type, protocol)) < 0)
            return (-1);
        if (connect(fd, addr, alen) == 0) {
            printf("connected accepted\n");
            return (fd);
        }
    close(fd);

    // delay
    if (numsec <= MAXSLEEP/2)
        sleep(numsec);
    }
    return (-1);
}
