#include "apue.h"
#include <signal.h>

int
main()
{
    char str[1024];
    memset(str, 0, 1024);
    psignal(SIGTSTP, str);
    printf("%s", str);
}
