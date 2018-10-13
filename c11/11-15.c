#include "apue.h"
#include <pthread.h>

struct msg {
    struct msg *m_next;
    /** more stuff*/
    char m_ch;  // print
};

struct msg *workq;

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;

void
print_msg(struct msg *mp)
{
    printf("\t%c\n", mp->m_ch);
    free(mp);
}

void *
process_msg(void * arg)
{
    struct msg *mp;

    for (;;) {
        pthread_mutex_lock(&qlock);
        while (workq == NULL)
            pthread_cond_wait(&qready, &qlock); // atomic release and lock
        mp = workq;
        workq = workq->m_next;
        pthread_mutex_unlock(&qlock);

        /** processing the msg */
        print_msg(mp);
    }
}


void
enqueue_msg(struct msg *mp)
{
    pthread_mutex_lock(&qlock);
    mp->m_next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
}

void
add_msg(char c)
{
    struct msg *nmsg;

    nmsg = (struct msg *)malloc(sizeof(struct msg));
    nmsg->m_ch = c;
    nmsg->m_next = NULL;
    enqueue_msg(nmsg);
}


int
main()
{
    char str[] = "miku!miku!!";
    int err;
    pthread_t ntid;
    char *cp;

    err = pthread_create(&ntid, NULL, process_msg, NULL);
    if (err != 0)
        err_exit(err, "thread exit");
    printf("thread start:\n");

    for (cp = str; *cp != 0; cp++)
        add_msg(*cp);


    sleep(5);
    exit(0);

}

