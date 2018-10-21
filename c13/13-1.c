#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void
daemonize(const char *cmd)
{
    int              i, fd0, fd1, fd2;
    pid_t            pid;
    struct rlimit    rl;
    struct sigaction sa;

    umask(0);

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err_sys("%s, can't get file limit", cmd);

    // new session
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid != 0)
        exit(0);

    setsid();


    // become a orphan process
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("ignore sighup error");
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid != 0)
        exit(0);

    if (chdir("/") < 0)
        err_quit("change directory error");

    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; i++)
        close(i);

    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptor %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}

int
main(void)
{
    daemonize("13-1 daemon");
    pause();
    exit(0);
}

