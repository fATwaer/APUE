#include "apue.h"
#include <pthread.h>

int 
main()
{
    pthread_attr_t attr;
    size_t         stacksize, guardsize;
    void *         addr;

    pthread_attr_init(&attr);
    pthread_attr_getstack(&attr, &addr, &stacksize);
    pthread_attr_getguardsize(&attr, &guardsize);

    printf("stack at: %p, size: %x\n", addr, stacksize);
    printf("guardsize: %x\n", guardsize);
}

