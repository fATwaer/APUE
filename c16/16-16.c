#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define BUFLEN 128

extern int connect_retry(int, int, int, const struct sockaddr*,
                         socklen_t);

void
print_uptime(int sockfd)
{
    int     n;
    char    buf[BUFLEN];
    printf("1\n");

    while ((n = recv(sockfd, buf, BUFLEN, 0)) > 0)
        write(STDOUT_FILENO, buf, n);
    if (n < 0)
        err_sys("recv error");
}


int
main(int argc, char *argv[])
{
    struct addrinfo *ailist, *aip;
    struct addrinfo  hint;
    int              sockfd, err;
    char             str[] = "ruptime";
    char             *str2 = "ruptime";
    if (argc != 2)
        err_sys("usage: ruptime hostname");

    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    printf("%s\n", argv[1]);
    if ((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0)
        err_quit("getaddrinfo error: %s", err);
    err_sys("error\n");
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = connect_retry(aip->ai_family, SOCK_STREAM, 0,
                                    aip->ai_addr, aip->ai_addrlen)) < 0) {
                                        err = errno;

        } else {
            print_uptime(sockfd);
            exit(0);
        }
    }
    err_exit(err, "can't connect to %s", argv[1]);
}

