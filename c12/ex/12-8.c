#include <time.h>
#include <stdio.h>


int 
main()
{
    struct timespec t;
    t.tv_sec = -5;
    t.tv_sec = 20;
    clock_nanosleep(0, 0, &t, NULL);
    printf("1\n");
}
