## 11-1

just convert stack allocation to heap allocation.
``` C
void *
thr_fn1(void *arg)
{
    struct foo *fp;

    fp = (struct foo *)malloc(sizeof(struct foo));
    fp->a = 1;
    fp->b = 2;
    fp->c = 3;
    fp->d = 4;

    printfoo("thread 1:\n", fp);
    pthread_exit((void *)fp);
}

```

## 11-2

``` C
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
``` 
blog

## 11-3

Although I have done it before, it still have problem to solve. when I insert job into queue and send resume signal to all thread(by `pthread_cond_broadcast()`), something happens called `thundering herd`.

 
