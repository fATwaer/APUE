#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXSTRINGSZ 4096

static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void
key_deconstruct()
{
    printf("calling deconstruction ..\n");
}

static void
thread_init(void)
{
    pthread_key_create(&key, key_deconstruct);
}

char *
getenv(const char *name)
{
    int     i, len;
    char    *envbuf;

    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex);
    printf("thread %lu\n", (unsigned long)pthread_self());
    envbuf = (char *)pthread_getspecific(key);
    if (envbuf == NULL) {
        envbuf = malloc(MAXSTRINGSZ);
        if (envbuf == NULL) {
            pthread_mutex_unlock(&env_mutex);
            return (NULL);
        }
        pthread_setspecific(key, envbuf);
    }
    len = strlen(name);
    for (i = 0; environ[i] != NULL; i++) {
        if ((strncmp(name, environ[i], len) == 0) &&
            (environ[i][len] == '=')) {
                strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
                pthread_mutex_unlock(&env_mutex);
                return (envbuf);
            }
    }
    pthread_mutex_unlock(&env_mutex);
    return (NULL);
}


void *
fn(void *arg)
{
    printf("PATH = %s\n", getenv("PATH"));
    return (0);
}

int
main()
{
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, fn, NULL);
    pthread_create(&tid2, NULL, fn, NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    exit(0);
}

