#include "apue.h"
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>


#define NTHR    8               // number of thread
#define NUMNUM  8000000L        // number of numbers to sort
#define TNUM   (NUMNUM/NTHR)    // number to sort per thread


long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;
#ifdef SOLARIS
#define heapsort qsort
#else
#include "lib/heapsort.h"
#endif // SOLARIS

#ifdef DEBUG
pthread_mutex_t print = PTHREAD_MUTEX_INITIALIZER;
#endif

void *
thr_fn(void *arg)
{
    long idx = (long)arg;
    int i;

#ifdef DEBUG
    pthread_mutex_lock(&print);
    printf("thread(%lu) sort:", (unsigned long)pthread_self());
    for (i = idx; i < idx + 2; i++)
        printf("%d ", nums[i]);
    printf("  ... ...   ");
    for (i = idx+TNUM-2; i < idx+TNUM; i++)
        printf("%d ", nums[i]);
    printf("\n");
    pthread_mutex_unlock(&print);
#endif // DEBUG
    heapsort(&nums[idx], TNUM);
#ifdef DEBUG
    printf("thread(%lu) sorted:", (unsigned long)pthread_self());
    for (i = idx; i < idx + 4; i++)
        printf("%d ", nums[i]);
    printf("  ... ...   ");
    for (i = idx+TNUM-4; i < idx+TNUM; i++)
        printf("%d ", nums[i]);
    printf("\n");
    pthread_mutex_destroy(&print);
#endif // DEBUG
    pthread_barrier_wait(&b);

    return ((void *)0);
}

void
_merge()
{
    long    idx[NTHR];
    long    i, minidx, sidx, num;

    for (i = 0; i < NTHR; i++)
        idx[i] = i * TNUM;
    for (sidx = 0; sidx < NUMNUM; sidx++) {
        num = LONG_MAX;
        for (i = 0; i < NTHR; i++) {
            if ((idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num)) {
                num = nums[idx[i]];
                minidx = i;
            }
        }
        snums[sidx] = nums[idx[minidx]];
        idx[minidx]++;
    }
}


int
main(int argc, char *argv[])
{
    unsigned long       i;
    struct timeval      start, end;
    long long           startusec, endusec;
    double              elapsed;
    int                 err;
    pthread_t           tid;

    // initial set of numbers
    srandom(1);
    for (i = 0; i < NUMNUM; i++)
        nums[i] = random();

    // create 8 thread to sort
    setbuf(stdout, NULL);
    gettimeofday(&start, NULL);
    pthread_barrier_init(&b, NULL, NTHR+1);
    for (i = 0; i < NTHR; i++) {
        err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
        if (err != 0)
            err_exit(err, "can't create thread");
    }

    pthread_barrier_wait(&b);
    _merge();
    gettimeofday(&end, NULL);

    startusec = start.tv_sec * 1000000 + start.tv_usec;
    endusec = end.tv_sec * 1000000 + start.tv_usec;
    elapsed = (double)(endusec - startusec) /1000000.0;
    printf("sort took %4.f seconds\n", elapsed);
    for (i = 0; i < 5; i++)
        printf("%ld ", snums[i]);
    printf("   ... ...    ");
    for (i = NUMNUM - 5; i < NUMNUM; i++)
        printf("%ld ", snums[i]);
    printf("\n");

    exit(1);
}



