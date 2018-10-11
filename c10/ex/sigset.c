#include "apue.h"
#include <signal.h>

int
sigopt(sigset_t *set)
{
    unsigned long int *p = (unsigned long int *)set;
    return ((*p & (1 << (SIGINT - 1))) != 0);
}

int
main()
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigopt(&mask);

    printf("v: %d\n", sigopt(&mask));
}
