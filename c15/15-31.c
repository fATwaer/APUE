#include "apue.h"
#include <sys/shm.h>


#define ARRAY_SIZE  40000
#define MALLOC_SIZE 100000
#define SHM_SIZE    100000
#define SHM_MODE    0600 /** read and write*/

static char var = 1;
char array[ARRAY_SIZE];

int
main(void)
{
    char stack_array[ARRAY_SIZE] = {1};
    int  shmid;
    char *ptr, *shmptr;

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

    if (shmctl(shmid, IPC_RMID, 0) < 0) // remove (own reference count)
        err_sys("shmctl error");

    exit(0);
}

