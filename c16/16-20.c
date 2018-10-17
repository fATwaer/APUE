#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <syslog.h>

#define BUFLEN 128
#define MAXADDRLEN 256

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif // HOST_NAME_MAX

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void
server(int sockfd)
{
    int         n;
    socklen_t   alen;
    FILE        *fp;
    char        buf[BUFLEN];
    char        abuf[BUFLEN];
    struct sockaddr *addr = (struct sockaddr *)abuf;


    set_cloexec(sockfd);
    for (;;) {
            alen = MAXADDRLEN;
            if ((n = recvfrom(sockfd, buf, BUFLEN, 0, addr, &alen)) < 0) {
                syslog(LOG_ERR, "ruptimed: recvfrom error: %s",
                       strerror(errno));
                exit(1);
            }
            if ((fp = popen("uptime", "r")) == NULL) {
                sprintf(buf, "error: %s\n", strerror(errno));
                sendto(sockfd, buf, strlen(buf), 0, addr, alen);
            } else {
                if (fgets(buf, BUFLEN, fp) != NULL)
                    sendto(sockfd, buf, strlen(buf), 0, addr, alen);
                pclose(fp);
            }
    }
}


int
main(int argc, char *argv[])
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;
    int             sockfd, err, n;
    char            *host;

    if (argc != 1)
        err_quit("usage: ruptimed");
    if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
        n = _SC_HOST_NAME_MAX;
    if ((host = (char *)malloc(n)) == NULL)
        err_sys("malloc error");
    if (gethostname(host, n) < 0)       // get local host name
        err_sys("gethostname error");

    daemonize("ruptimed");    // fork -> child
                                //          fork -> child
                                //                   fork -> child (daemon)

    memset(&hint, 0, sizeof(hint));
    hint.ai_flags = AI_CANONNAME;
    hint.ai_socktype = SOCK_DGRAM;  /// UDP
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {
        syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s", gai_strerror(err));
        printf("getaddrinfo error = %s\n", gai_strerror(err));
        exit(0);
    }

    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = initserver(SOCK_DGRAM, aip->ai_addr, aip->ai_addrlen, 0)) >= 0) { // replace `QLEN` because UDP need not listening.
            server(sockfd);
            exit(0);
        }
        
    }
    printf("exit\n");
    exit(1);
}


