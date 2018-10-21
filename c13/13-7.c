#include "apue.h"
#include <pthread.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

sigset_t mask;

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


void
reread(void)
{

}


void *
thr_fn(void *arg)
{
    int err,signo;
    for (;;) {
        err = sigwait(&mask, &signo);
        if (err != 0) {
            syslog(LOG_ERR, "SIGWAIT ERROR");
            exit(1);
        }

        switch (signo) {
        case SIGHUP:
            syslog(LOG_ERR, "Re-reading configuration file");
            reread();
            break;
        case SIGTERM:
            syslog(LOG_ERR, "got SIGTERM; exiting");
            exit(0);
        default:
            syslog(LOG_INFO, "unexpected signal %d\n", signo);
        }
    }
    return (0);
}


int
main(int argc, char *argv[])
{
    int         err;
    pthread_t   tid;
    char        *cmd;
    struct sigaction sa;


    if ((cmd = strrchr(argv[0], '/')) == NULL)
        cmd = argv[0];
    else
        cmd++;

    daemonize(cmd);

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("%s: can't restore sighup");
    sigfillset(&mask);
    if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
        err_exit(err, "SIG_BLOCK ERROR");


    err = pthread_create(&tid, NULL, thr_fn, 0);
    if (err != 0)
        err_exit(err, "create thread error");
    pthread_join(tid, NULL);
    exit(0);
}

