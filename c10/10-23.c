#include "apue.h"
#include <sys/wait.h>
#include <errno.h>

static void sig_int(int);

volatile sig_atomic_t quitflag;

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
main()
{
    sigset_t newmask, oldmask, zeromask;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal(SIGINT) error");
    if (signal(SIGQUIT, sig_int) == SIG_ERR)
        err_sys("signal(SIGQUIT) error");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("sig_block error");

    while (quitflag == 0)
        sigsuspend(&zeromask);

    quitflag = 0;


    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("sig_setmask error");


    exit(0);
}


static void
sig_int(int signo)
{
    if (signo == SIGINT)
        printf("\nInterrupt\n");
    else if (signo == SIGQUIT)
        quitflag = 1;
}

