#include "apue.h"
#include <sys/shm.h>


#define ARRAY_SIZE  40000
#define MALLOC_SIZE 100000
#define SHM_SIZE    100000
#define SHM_MODE    0600 /** read and write*/

static char var = 1;
char array[ARRAY_SIZE];

typedef long int ptr;

typedef struct {
    char data[16];
    int  id;
    ptr nxt;
}Node;

char *shmptr;

void
shm_linklist_print()
{
    setbuf(stdout, NULL);
    Node *p = (Node *)shmptr;
    do {
        printf("id = %d, data = '%s'\n", p->id, p->data);
        p = (Node *)((char *)shmptr + p->nxt);
    } while (p->nxt != -1);
        printf("id = %d, data = '%s'\n", p->id, p->data);


}



int
main(void)
{
    int  shmid;
    char *ptr ;

    // shared memory
    if ((shmptr = shmat(753673, 0, 0)) == (void *)-1)
        err_sys("shmat error");
    printf("[shared memory]: %p -> %p\n", (void *)shmptr,
           (void *)shmptr+SHM_SIZE);
 

    shm_linklist_print();


    exit(0);
}

