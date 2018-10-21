#include "apue.h"
#include <pthread.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAXSTRINGSZ 4096

extern char **environ;

static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t mutex;

static void
thread_init(void)
{
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}


int
putenv_r(char *name)
{
    int     endpos, len, i;
    sigset_t mask, oldmask;


    sigfillset(&mask);
    if (sigprocmask(SIG_BLOCK, &mask, &oldmask) < 0)
        err_sys("set block error");
    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&mutex);

    for (i = 0; name[i] != '='; i++);
    if (name[i] != '=')
        err_sys("format error");
    len = i;
    for (i = 0; environ[i] != NULL; i++) {
        if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '=')) {

                for (endpos = len+1; environ[i][endpos] != 0; endpos++);
                environ[i][endpos] = ':';
                strncpy(&environ[i][endpos+1], &name[len+1], strlen(name) - len);
                if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
                    err_sys("set_mask error");
                return (0);

            }

    }
    // inexistent
    environ[i] = malloc(MAXSTRINGSZ);
    strncpy(environ[i], name, strlen(name));
    environ[i][strlen(name)] = 0;
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("set_mask error");
    return (0);
}


int
main(void)
{
    char PATH[] = "PATH=/local/random";
    char env1[] = "AAA=mememe";
    char env2[] = "AAA=yoyoyo";
    putenv_r(PATH);
    putenv_r(env1);
    putenv_r(env2);
    printf("%s\n", getenv("AAA"));
    printf("%s\n", getenv("PATH"));
    exit(0);
}

