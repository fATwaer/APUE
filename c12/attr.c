#include "apue.h"
#include <pthread.h>

void *
thr_fn(void *arg)
{
    while (1)
    {
        printf("detached thread ...\n");
        sleep(1);
    }
    return ((void *)0);
}

int
main()
{
    pthread_t       tid;
    int             i, ret;
    pthread_attr_t  attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid, &attr, thr_fn, NULL);
    pthread_attr_destroy(&attr);
    
    for (i = 0; i < 3; i++)
    {
        printf("main thread ...\n");
        sleep(1);
    }

    ret = pthread_join(tid, NULL);
    printf("pthread_join ret %d\n", ret);
    pause();
    exit(0);
}


