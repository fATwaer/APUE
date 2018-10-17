#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define BUFLEN 128

extern int connect_retry(int, int, int, const struct sockaddr*,
                         socklen_t);

void
sigalrm(int signo)
{
    fprintf(stderr, "sigalrm invoke\n");
}

Sigfunc *
signal(int signo, Sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif // SA_INTERRUPT

    } else {
        act.sa_flags |= SA_RESTART;
    }

    if (sigaction(signo, &act, &oact) < 0)
        return (SIG_ERR);
    return (oact.sa_handler);
}

#define TIMEOUT 5
void
print_uptime(int sockfd, struct addrinfo *aip)
{
    int     n;
    char    buf[BUFLEN];

    buf[0] = 0;
    if (sendto(sockfd, buf, 1, 0, aip->ai_addr, aip->ai_addrlen) < 0)
        err_sys("sendto erro");
    alarm(TIMEOUT);
    if ((n = recvfrom(sockfd, buf, BUFLEN, 0, NULL, NULL)) < 0) {
        if (errno != EINTR)
            alarm(0);
        err_sys("recv error");
    }
    alarm(0);
    write(STDOUT_FILENO, buf, n);
}


int
main(int argc, char *argv[])
{
    struct addrinfo *ailist, *aip;
    struct addrinfo  hint;
    int              sockfd, err;

    if (argc != 2)
        err_sys("usage: ruptime hostname");
    signal(SIGALRM, sigalrm);               // established handler for SIGALRM
    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_DGRAM;         // use UDP transmission
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if ((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0)
        err_quit("getaddrinfo error: %s", gai_strerror(err));

    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = connect_retry(aip->ai_family, SOCK_DGRAM, 0,
                                    aip->ai_addr, aip->ai_addrlen)) < 0)
        {
            err = errno;

        } else {
            print_uptime(sockfd, aip);
            exit(0);
        }
    }
    err_exit(err, "can't connect to %s", argv[1]);
}


