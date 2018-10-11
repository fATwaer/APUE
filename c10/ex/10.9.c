#include "apue.h"
#include <signal.h>
#include <errno.h>

#ifndef SIG2STR_MAX
#define SIG2STR_MAX 32
#endif // SIG2STR_MAX


int
my_sig2str(int signo, char *str)
{
    int i;
    char *addr;

    if ((addr = strsignal(signo)) == NULL)
        return (-1);

    i = 0;
    while (i < SIG2STR_MAX && addr[i] != 0)
    {
        str[i] = addr[i];
        i++;
    }

    return (0);
}

int
_exsist(sigset_t *mask, int signo)
{
    unsigned long int*set = (unsigned long int*)mask;
    return ((*set & (1 << (signo - 1))) != 0);
}

void
pr_mask(const char *name)
{
    sigset_t mask;
    int errno_save;
    int signo; //shift
    char str[SIG2STR_MAX];

    errno_save = errno; // ?
    if (sigprocmask(0, NULL, &mask))
        err_sys("sigprocmask erro");

    signo = 1;
    printf("%s\n", name);
    while (signo < 32)
    {
        memset(str, 0, SIG2STR_MAX);
        if (_exsist(&mask, signo))
        {
            my_sig2str(signo, str);
            printf("%s\n", str);
        }
        signo++;
    }
    errno = errno_save;
}



int
main()
{
    sigset_t newmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);
    sigaddset(&newmask, SIGALRM);
    sigaddset(&newmask, SIGCHLD);
    sigaddset(&newmask, SIGBUS);

    if (sigprocmask(SIG_BLOCK, &newmask, NULL) < 0)
        err_sys("sigblock error");
    pr_mask("main: ");
}


