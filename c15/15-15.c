#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
    char    line[MAXLINE];
    FILE    *fpin;

    if ((fpin = popen("./myuclc", "r")) == NULL)
        err_sys("popen error");

    for (;;) {
        fputs("prompt>", stdout);
        fflush(stdout);
        if (fgets(line, MAXLINE, fpin) == NULL)
            break;
        if (fputs(line, stdout) == EOF)
            err_sys("fputs error");
    }

    if (pclose(fpin) == -1)
        err_sys("pclose error");
    putchar('\n');
    exit(0);
}

