#include "apue.h"
#include <errno.h>
#include <sys/wait.h>


/**
/*
/*      #define	SIGCLD		SIGCHLD	/* Old System V name */
/*
**/




static void sig_cld(int);

int
main()
{
    pid_t pid;

    if (signal(SIGCLD, sig_cld))
        perror("signal error");
    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        sleep(2);
        _exit(0);
    }

    pause();
    exit(0);
}


static void
sig_cld(int signo)
{
    pid_t pid;
    int status;

    printf("SIGCLD received\n");

    if (signal(SIGCLD, sig_cld) == SIG_ERR)
        perror("signal error");

    if ((pid = wait(&status)))
        perror("wait error");

    printf("pid = %d\n", pid);
}

