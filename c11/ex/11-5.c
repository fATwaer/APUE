#include "apue.h"
#include <pthread.h>

static int count = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  ready = PTHREAD_COND_INITIALIZER;

int
_barrier_init(pthread_mutex_t *mtx, int n)
{
    pthread_mutex_lock(mtx);

    count = n;

    pthread_mutex_unlock(mtx);

    return 0;
}


int
_barrier_wait(pthread_mutex_t *mtx)
{
    pthread_mutex_lock(mtx);

    count--;
    if (count != 0)
        while (count != 0)
            pthread_cond_wait(&ready, mtx);
    else
    {
        pthread_cond_broadcast(&ready);
        pthread_mutex_unlock(mtx);
        return (PTHREAD_BARRIER_SERIAL_THREAD);
    }

    pthread_mutex_unlock(mtx);
    return (0);
}

void *
thr_fn(void *arg)
{
    printf("thread(%lu) -> barrier\n", (unsigned long)pthread_self());
    _barrier_wait(&mtx);
    printf("thread(%lu) out barrier\n", (unsigned long)pthread_self());
    return ((void *)0);
}


int
main()
{
    pthread_t tid;
    int         i;

    setbuf(stdout, NULL);
    printf("main thread = %lu\n", (unsigned long)pthread_self());
    _barrier_init(&mtx, 4+1);
    for (i = 0; i < 4; i++)
    {
        pthread_create(&tid, NULL, thr_fn, NULL);
    }

    _barrier_wait(&mtx);
    printf("main thread exiting\n");
    sleep(1);       //main thread may quick than other four thread.
    exit(0);
}


