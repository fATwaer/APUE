#include "apue.h"
#include <stdio.h>


extern int cli_conn(const char *name);

int 
main()
{
    if (cli_conn("UNIX.socket") < 0)
        err_sys("error");
    else
        printf("ok\n");

}
