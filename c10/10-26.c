#include "apue.h"
#include <sys/wait.h>
#include <errno.h>
static void sig_int(int);
static void sig_chld(int);



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

int
mysystem(const char *cmdstring)
{
    pid_t pid;
    int status;

    if (cmdstring == NULL)
        return 1;
    if ((pid = fork()) < 0)
        status = -1;
    else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127);
    } else {
        while (waitpid(pid, &status, 0) < 0)
            if (errno != EINTR) {
                status = -1;
                break;
            }    
    }
    
    return (status) ;
}

int
main()
{
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("sigint err");
    if (signal(SIGCHLD, sig_chld) == SIG_ERR)
        err_sys("sigchld err");
    printf("openning program ed...\n");
    if (mysystem("/bin/ed") < 0)
        err_sys("system err");

    exit(0);
}



static void
sig_int(int signo)
{
    printf("caught SIGINT\n");
}

static void
sig_chld(int signo)
{
    printf("caught SIGCHLD\n");
}

