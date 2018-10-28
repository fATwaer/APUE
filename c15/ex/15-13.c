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
int flag = 0;

void
shm_linklist_insert(ptr dst, char *data, int len)
{
    Node nnode, *p;

    p = (Node *)shmptr;
    if (flag == 0) {
        nnode.id = 1;
        flag = 1;
    } else {
        while (p->nxt != -1)
            p = (Node *)((char *)shmptr + p->nxt);
        p->nxt = dst;
        nnode.id = p->id + 1;
    }
    nnode.nxt = -1;
    nnode.data[len] = '\0';
    memmove(nnode.data, data, len);
    memmove((shmptr + dst), &nnode, sizeof(nnode));

}

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
    char stack_array[ARRAY_SIZE] = {1};
    int  shmid;
    char *ptr ;

    printf("[global var]: %p\n", (void *)&var);
    printf("[array[]]: %p -> %p \n", (void *)&array[0],
           (void *)&array[ARRAY_SIZE]);
    printf("[stack]: %p\n", (void *)&shmid);

    printf("[initialized stack_array]: %p -> %p\n",
           (void *)&stack_array[0], (void *)&stack_array[ARRAY_SIZE]);

    if ((ptr = malloc(MALLOC_SIZE)) == NULL)
        err_sys("mallock error");
    printf("[malloced]: %p -> %p\n", (void *)ptr,
           (void *)ptr + MALLOC_SIZE);

    // shared memory
    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)
        err_sys("shmget error");
    if ((shmptr = shmat(shmid, 0, 0)) == (void *)-1)
        err_sys("shmat error");
    printf("[shared memory]: %p -> %p\n", (void *)shmptr,
           (void *)shmptr+SHM_SIZE);

    printf("id %d\n", shmid);
    // create linklist
    shm_linklist_insert(0, "ikbc", 4);
    shm_linklist_insert(0+sizeof(Node), "codeblock", 9);
    shm_linklist_insert(10*sizeof(Node), "be quiet!", 9);
    shm_linklist_print();

    pause();
    if (shmctl(shmid, IPC_RMID, 0) < 0) // remove (own reference count)
        err_sys("shmctl error");

    exit(0);
}

