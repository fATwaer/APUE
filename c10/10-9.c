#include "apue.h"
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf env_alrm;


unsigned int sleep2(unsigned int);
static void sig_int(int);
static void sig_alrm(int);

int 
main()
{
    unsigned int unslept;
    
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal(SIGINT) error");
    unslept = sleep2(20);
    printf("sleep2 returned %d\n", unslept);
    exit(0);
}

static void
sig_int(int signo)
{

    int i;
    volatile int k;
    int j;

    printf("\nsig_int handler starting\n");
    // the entire __for__ loop costs about 11s.
    for (i = 0; i < 500000; i++)
        for (j = 0; j < 10000; j++)
            k += i * j;

    printf("sig_int handler finished\n");
}

unsigned int
sleep2(unsigned int seconds)
{
    if ((signal(SIGALRM, sig_alrm)) == SIG_ERR)
        return (seconds);
    if (setjmp(env_alrm) == 0) {
        alarm(seconds);
        pause();
    }

    return (alarm(0));
}

static void
sig_alrm(int signo)
{
    longjmp(env_alrm, 1);
}




