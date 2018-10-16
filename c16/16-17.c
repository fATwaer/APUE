#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <syslog.h>

#define BUFLEN 128
#define QLNE 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif // HOST_NAME_MAX

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void
server(int sockfd)
{
    int         clfd;
    FILE        *fp;
    char        buf[BUFLEN];

    set_cloexec(sockfd);
    for (;;) {
        if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
            syslog(LOG_ERR, "ruptimed: accept error: %s", strerror(errno));
            exit(1);
        }
        set_cloexec(clfd);
        if ((fp = popen("uptime", "r")) == NULL) {
            sprintf(buf, "error : %s\n", strerror(errno));
            send(clfd, buf, strlen(buf), 0);
        } else {
            while (fgets(buf, BUFLEN, fp) != NULL)
                send(clfd, buf, strlen(buf), 0);
            pclose(fp);
        }
        close(clfd);
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

    printf("daemonize, host = %s\n", host);
    //daemonize("ruptimed");
    memset(&hint, 0, sizeof(hint));
    hint.ai_flags = AI_CANONNAME;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {
        syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s", gai_strerror(err));
        printf("getaddrinfo error = %s\n", gai_strerror(err));
        exit(0);
    }

    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen, QLNE)) >= 0) {
            server(sockfd);
            exit(0);
        }
    }
    exit(1);
}

