#include "apue.h"
#include <stdlib.h>
#include <time.h>

void
pr_time()
{
    time_t t;
    struct tm *tmp;
    char timestr[64];

    time(&t);
    tmp = localtime(&t);
    
    strftime(timestr, 64, "time: %r, %a %b %d, %Y", tmp);
    printf("%s\n", timestr);
}








int
main(void)
{
    int i;

    pr_time();
    i = 0;
    while (1) {
        i++;
        sleep(60);
        if (i == 5) {
            pr_time();
            i = 0;
        }
    }
}
