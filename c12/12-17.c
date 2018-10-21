#include "apue.h"
#include <pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void
prepare(void)
{
    int err;

    printf("preparing locks...\n");
    if ((err = pthread_mutex_lock(&lock1)) < 0)
        err_cont(err, "can't lock lock1 in prepare handler");
    if ((err = pthread_mutex_lock(&lock2)) < 0)
        err_cont(err, "can't lock lock2 in prepare handler");
}

void
parent(void)
{
    int err;

    printf("parent unlocking locks...\n");
    if ((err = pthread_mutex_unlock(&lock1)) < 0)
        err_cont(err, "parent can't unlock lock1");
    if ((err = pthread_mutex_unlock(&lock2)) < 0)
        err_cont(err, "parent can't unlock lock2");
}

void
child(void)
{
    int err;

    printf("child unlocking locks...\n");
    if ((err = pthread_mutex_unlock(&lock1)) < 0)
        err_cont(err, "child can't unlock lock2");
    if ((err = pthread_mutex_unlock(&lock2)) < 0)
        err_cont(err, "child can't unlock lock2");
}

void *
thr_fn(void *arg)
{
    printf("thread started...\n");
    pause();
    return (0);
}

void
test_fn(void)
{
    printf("register sequence is 2\n");
}

int
main(void)
{
    int     err;
    pid_t   pid;
    pthread_t tid;

    if ((err = pthread_atfork(prepare, parent, child)) != 0)
        err_exit(err, "install fork handler error");
    //pthread_atfork(test_fn, NULL, NULL);
    if ((err = pthread_create(&tid, NULL, thr_fn, 0)) != 0)
        err_exit(err, "create error");

    sleep(2);
    printf("about to fork ... \n");

    if ((pid =fork()) < 0)
        err_quit("fork failed");
    else if (pid == 0)
        printf("child returned from fork\n");
    else
        printf("parent returned from fork\n");

    exit(0);
}

