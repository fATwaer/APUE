#include "apue.h"
#include <signal.h>
#include <errno.h>

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

static void
sig_alrm(int signo)
{
    printf("caught SIGALRM\n");
}

#define KBSZ (1024)
#define MBSZ (1024 * KBSZ)
#define GBSZ (1024 * MBSZ)

int
main()
{
    void *buff;
    FILE *fp;
    int ret;
    
    buff = (void *)malloc(sizeof(char) * GBSZ);
    memset(buff, '9', GBSZ);
    
    if ((fp = fopen("BIG.file", "w+")) == NULL)
        err_sys("fopen error");
    if ((signal(SIGALRM, sig_alrm)) == SIG_ERR)
        err_sys("SIGALRM error");

    alarm(1);
    if ((ret = fwrite(buff, sizeof(char), GBSZ, fp)) != GBSZ)
    {
        fprintf(stderr, "fwrite return = %d\n", ret);
        err_sys("fwrite error");
    }
    printf("end fwrite\n");
    exit(0);

}


