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

    addr = strsignal(signo);
    i = 0;
    while (i < SIG2STR_MAX && addr[i] != (char*)0)
    {
        str[i] = addr[i];
        i++;
    }
}

int
main()
{
    char str[SIG2STR_MAX];
    my_sig2str(SIGINT, str);
    printf("%s\n", str);
}

