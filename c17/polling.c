#include <apue.h>
#include <poll.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/socket.h>

#define MAXMSZ 512
int
main()
{
    pid_t               pid;
    int                 fd[2];
    struct pollfd       pfd;
    char                buf[MAXMSZ];
    int                 n;

    setbuf(stdout, NULL);
    pipe(fd);
    if ((pid = fork()) < 0)
        err_sys("error fork");
    else if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        while ((n = read(STDIN_FILENO, buf, MAXMSZ)) > 0) {
            sleep(5);
            if (write(STDOUT_FILENO, buf, n) != n)
                err_sys("write error");

            if (n < 0)
                err_sys("read error");
        }

        exit(0);
    }
    close(fd[1]);

    pfd.events = POLLIN;
    pfd.fd = fd[0];
    for (;;) {
        printf("polling ... \n");
        if (poll(&pfd, 1, -1) < 0)
            err_sys("poll error");
        printf("polling end ... \n");

        if (pfd.revents & POLLIN) {
            if ((n = read(pfd.fd, buf, sizeof(buf))) < 0)
                err_sys("read error");
            buf[n] = 0;
            printf("recv %s\n", buf);
        }

    }
    exit(0);
}


