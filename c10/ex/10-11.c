#include "apue.h"
#include <sys/resource.h>
#include <fcntl.h>
#include <errno.h>
/*
 *   fork from 3-3.c
 */



#define BUFFSIZE 100

static volatile sig_atomic_t sigflag;

Sigfunc *
signal_intr(int signo, Sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif // SA_INTERRUPT

    if (sigaction(signo, &act, &oact) < 0)
        return (SIG_ERR);
    return (oact.sa_handler);
}

static void
sig_xfsz(int signo)
{
    sigflag = 1;
    fprintf(stderr, "caught SIGXFSZ\n");
}


int 
main()
{
	int n, ret, fd;
	char buf[BUFFSIZE];
    struct rlimit limit;
    int fresource;
    sigset_t mask, oldmask;

    /*set R_LIMIT_FSIZE to 1024*/
    if (getrlimit(RLIMIT_FSIZE, &limit) < 0)
        err_sys("getrlimit error");
    
    limit.rlim_cur = 1024;
    
    if (setrlimit(RLIMIT_FSIZE, &limit) < 0)
        err_sys("setrlimit error");

    /* catch SIGXFSZ*/
    if (signal_intr(SIGXFSZ, sig_xfsz) == SIG_ERR)
        err_sys("sigxfsz error");

    if ((fd = (open("out.file", O_RDWR|O_CREAT|O_TRUNC, 0644))) < 0)
        err_sys("open file error");
	
    sigemptyset(&mask);
    sigaddset(&mask, SIGXFSZ);
    
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) 
		if ((ret = write(fd, buf, n)) != n) {
            sigprocmask(SIG_SETMASK, &oldmask, NULL);
            pause();
            printf("write returns %d\n", ret);
			err_sys("write error");
        }

	if (n < 0)
		err_sys("read error");

	exit(0);
}
