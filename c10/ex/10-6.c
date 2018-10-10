#include "apue.h"
#include <signal.h>

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;
static void _TIME_WAIT(void);
static void _WAIT_PARENT(void);
static void _WAIT_CHILD(void);
static void _TELL_CHILD(pid_t);
static void _TELL_PARENT(pid_t);
/**
 *  SIGUSR1 P->C
 *  SIGUSR2 C->P
*/


int critical_action(FILE* , int, char *);


Sigfunc *
signal(int signo, Sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif // SA_INTERRUPT

    } else {
        act.sa_flags |= SA_RESTART;
    }

    if (sigaction(signo, &act, &oact) < 0)
        return (SIG_ERR);
    return (oact.sa_handler);
}

static void
sig_usr(int signo)
{
   sigflag = 1;
}


int
main()
{
    FILE *fp;
    int n, m;
    pid_t pid;

    n = 0;

    /** write 0 to the file */
    if ((fp = fopen("tempfile", "w+")) == NULL)
        err_sys("open file error");

    if (fwrite(&n, sizeof(int), 1, fp) != 1)
        err_sys("fwrite error");

    _TIME_WAIT();
    /** fork */
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0){
    /** child increase first */
        while (1) {

            n = critical_action(fp, n, "child");
            sleep(1);

            _TELL_PARENT(getppid());
            _WAIT_PARENT();
        }

    }

    /** parent increase, waiting child signal*/
    while (1) {
        _WAIT_CHILD();

        n = critical_action(fp, n, "parent");
        sleep(1);

        _TELL_CHILD(pid);
    }




    exit(0);
}

int
critical_action(FILE* fp, int n, char *member)
{
    if (fseek(fp, 0, SEEK_SET) < 0)
        err_sys("fseek error");
    if (fread(&n, sizeof(int), 1, fp) != 1)
        err_sys("fread error");

    printf("%s read %d, write %d\n", member, n, n+1);
    n++;

    if (fseek(fp, 0, SEEK_SET) < 0)
        err_sys("fseek error");
    if (fwrite(&n, sizeof(int), 1, fp) != 1)
        err_sys("fwrite error");

    /** be care with here, must flush the date into disk*/
    /** standard I/O buffer */
    fflush(fp);
    return n;
}



static void
_TIME_WAIT(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("sigusr1 err");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("sigusr2 err");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("sig_block err");

}

static void
_TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1);
}


static void
_WAIT_PARENT(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;

    // reset
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("set_mask err");
}


static void
_TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);
}

static void
_WAIT_CHILD(void)
{
    while (sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("set_mask err");
}




