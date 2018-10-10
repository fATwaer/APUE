#include "apue.h"


static void sig_tstp(int);

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

#define BUFFSIZE 4096

int
main()
{
    int n;
    char buf[BUFFSIZE];

    if (signal(SIGTSTP, SIG_IGN) == SIG_DFL)
        signal(SIGTSTP, sig_tstp);

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");

    if (n < 0)
        err_sys("read error");

    exit(0);
}

static void
sig_tstp(int signo)
{
    sigset_t mask;

    // back terminal.
    printf("suspend and back to terminal\n");

    /** unblock sigtstp */
    sigemptyset(&mask);
    sigaddset(&mask, SIGTSTP);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    /** default signal handler */
    signal(SIGTSTP, SIG_DFL);

    printf("waiting SIGCONT ....\n");
    /** suspending and waiting to be revoked */
    kill(getpid(), SIGTSTP);

    signal(SIGTSTP, sig_tstp);

    /** continue ...*/
    printf("proc continue executing\n");
}


