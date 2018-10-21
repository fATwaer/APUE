#include "apue.h"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

extern int makethread(void *(*)(void *), void *);

struct to_info{
    void    (*to_fn)(void *);
    void    *to_arg;
    struct timespec to_wait;
};

#define SECTONSEC 1000000000

void *
timeout_helper(void *arg)
{
    struct to_info *tip;

    tip = (struct to_info *)arg;
    clock_nanosleep(CLOCK_REALTIME, 0, &tip->to_wait, NULL);
    (*tip->to_fn)(tip->to_arg);
    free(arg);
    return (0);
}

void retry(void *);

void
timeout(const struct timespec *when, void (*func)(void *), void *arg)
{
    struct timespec now;
    struct to_info  *tip;
    int             err;

    clock_gettime(CLOCK_REALTIME, &now);
    if ((when->tv_sec > now.tv_sec) ||
    (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec)) {
        tip = malloc(sizeof(struct to_info));
        if (tip != NULL) {
            tip->to_fn = func;
            tip->to_arg = arg;
            tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
            if (when->tv_nsec >= now.tv_nsec)
                tip->to_wait.tv_sec = when->tv_nsec - now.tv_nsec;
            else {
                tip->to_wait.tv_sec--;
                tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_nsec;
            }
            err = makethread(timeout_helper, (void *)tip);
            if (err == 0)
                return;
            else
                free(tip);
        }
    }

    (*func)(arg);
}


pthread_mutexattr_t attr;
pthread_mutex_t mutex;

void
retry(void *arg)
{
    struct timespec when;
    
    pthread_mutex_lock(&mutex);
    printf("retry ..\n");
//    clock_gettime()
//    timeout()
    sleep(5);
    pthread_mutex_unlock(&mutex);
}




int
main()
{
    int             err, condition, arg;
    struct timespec when;

    if ((err = pthread_mutexattr_init(&attr)) != 0)
        err_exit(err, "pthread_mutexattr_init failed");
    if ((err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0)
        err_exit(err, "settype failed");
    if ((err = pthread_mutex_init(&mutex, &attr)) != 0)
        err_exit(err, "init error");

    /* processing */

    pthread_mutex_lock(&mutex);
    condition = 1;
    if (condition) {

        clock_gettime(CLOCK_REALTIME, &when);
        when.tv_sec += 5;
       // sleep(5);
        timeout(&when, retry, (void *)((unsigned long)arg));
    }

    pthread_mutex_unlock(&mutex);

    sleep(12);
    exit(0);
}

