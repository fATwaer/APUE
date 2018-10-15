#include "apue.h"
#include <pthread.h>



struct job {
    struct job *j_next;
    struct job *j_prev;
    pthread_t   j_id;
    /** job */
    int (*j_add)(int);
    int         j_num;
};

struct queue {
    struct job      *q_head;
    struct job      *q_tail;
    pthread_rwlock_t q_lock;
};


int
queue_init(struct queue *qp)
{
    int err;

    qp->q_head = NULL;
    qp->q_tail = NULL;
    err = pthread_rwlock_init(&qp->q_lock, NULL);

    if (err != 0)
        return (err);

    return (0);
}

void
job_insert(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = qp->q_head;
    jp->j_prev = NULL;
    if (qp->q_head != NULL)
        qp->q_head->j_prev = jp;
    else
        qp->q_tail = jp;
    qp->q_head = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}


/** append a job on the tail of the queue. */
void
job_append(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = NULL;
    jp->j_prev = qp->q_tail;
    if (qp->q_tail != NULL)
        qp->q_tail->j_next = jp;
    else
        qp->q_head = jp;
    qp->q_tail = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

void
job_remove(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->q_lock);
    if (jp == qp->q_head) {
        qp->q_head = jp->j_next;
        if (qp->q_tail == jp)
            qp->q_tail = NULL;
        else
            jp->j_next->j_prev = jp->j_prev;
    } else if (jp == qp->q_tail) {
        qp->q_tail = jp->j_prev;
        jp->j_prev->j_next = jp->j_next;
    } else {
        jp->j_prev->j_next = jp->j_next;
        jp->j_next->j_prev = jp->j_prev;
    }
    pthread_rwlock_unlock(&qp->q_lock);
}


struct job *
job_find(struct queue *qp, pthread_t id)
{
    struct job *jp;

    if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
        return (NULL);

    for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
        if (pthread_equal(jp->j_id, id))
            break;

    pthread_rwlock_unlock(&qp->q_lock);
    return (jp);
}


/** following implement the instant  which  */
/** modify the job tid member when a thread */
/** is `suspend`                            */
int add(int);

struct job *
job_alloc(struct queue *qp, int num)
{
    struct job *jp;

    if ((jp = (struct job *)malloc(sizeof(struct job))) == NULL)
        return (NULL);

    jp->j_add = add;
    jp->j_num = num;
    jp->j_id = pthread_self();
    job_insert(qp, jp);

    return (jp);
}

int
add(int i)
{
    int sum;

    sum = 0;
    while (i)
        sum += i--;

    return sum;
}

/** thread suspend mutex*/
pthread_cond_t jready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t statmtx =  PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t b;
enum status {
    STOP    = 0,
    RUNNING = 1
};
static enum status t1st = STOP;


/** add job into queue*/
void *
th_func1(void *arg)
{
    job_alloc((struct queue *)arg, 10);

    job_alloc((struct queue *)arg, 9);

    job_alloc((struct queue *)arg, 8);

    job_alloc((struct queue *)arg, 7);

    return ((void *)0);
}

void *
th_func2(void *arg)
{
    struct job *jp;
    int sum;
//    struct queue *qp;


    pthread_mutex_lock(&statmtx);

    while (t1st == STOP) {
        printf("thread %lu is waiting resource..\n", (unsigned long)pthread_self());
        pthread_cond_wait(&jready, &statmtx);             /** when the pthread recived the signal, it will test the while loop confidion fisrt*/
    }
    printf("thread %lu is going to run\n", (unsigned long)pthread_self());
    pthread_mutex_unlock(&statmtx);



    jp = job_find((struct queue *)arg, pthread_self());

    job_remove((struct queue *)arg, jp);

    /** processing job */
    sum = jp->j_add(jp->j_num);
    printf("thread %lu caculate %d\n", (unsigned long)pthread_self(), sum);

    printf("return = %d, tid = %lu\n", pthread_barrier_wait(&b), (unsigned long)pthread_self());

    return ((void *)0);

}


void
th_resume(void)
{
    if (t1st == STOP) {
        pthread_mutex_lock(&statmtx);
        t1st = RUNNING;
        pthread_cond_broadcast(&jready);
        printf("thread resume signal send..\n");
        pthread_mutex_unlock(&statmtx);
    }
}

int
modify_tid(struct queue *qp, pthread_t tid1, pthread_t tid2)
{
    struct job *jp;

    pthread_rwlock_wrlock(&qp->q_lock);

    for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
        if (pthread_equal(jp->j_id, tid1))
            break;
    jp->j_id = tid2;

    pthread_rwlock_unlock(&qp->q_lock);

    return 0;
}



int
main(void)
{
    struct queue qn;
    int err;
    pthread_t tid1, tid2;
    queue_init(&qn);
    
    setbuf(stdout, NULL);
    err = pthread_create(&tid1, NULL, th_func1, &qn);
    if (err != 0)
        err_exit(err, "thread create error");
    pthread_join(tid1, NULL);

    pthread_barrier_init(&b, NULL, 4+1);
    for (int i = 0; i < 4; i++)
    {
        err = pthread_create(&tid2, NULL, th_func2, &qn);
        if (err != 0)
            err_exit(err, "thread create error");

        modify_tid(&qn, tid1, tid2);
    }
    th_resume();
    //sleep(1);
    printf("return = %d, main = %lu\n", pthread_barrier_wait(&b), (unsigned long)pthread_self());


    printf("thread %lu is main thread\n", (unsigned long)pthread_self());
    exit(0);

}

