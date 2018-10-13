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
