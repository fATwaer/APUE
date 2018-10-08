#include "apue.h"
#include <pwd.h>
static void
sig_user(int signo)
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else 
        err_dump("received signal %d\n", signo);
}


int
main(void)
{
    if (signal(SIGUSR1, sig_user) == SIG_ERR)
        err_sys("can't catch SIGUSER1");
    if (signal(SIGUSR2, sig_user) == SIG_ERR)
        err_sys("can't catch SIGUSER2");
    
    for (;;)
        pause();
}
