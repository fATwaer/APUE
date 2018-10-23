#include "apue.h"
#include <sys/msg.h>

#define MAXMSZ 512

struct mymesg{
    long mtype;
    char mtext[MAXMSZ];
};


int
main(int argc, char *argv[])
{

    key_t key;
    long qid;
    size_t nbytes;
    struct mymesg m;

    if (argc != 3)
        err_quit("argument");

    key = strtol(argv[1], NULL, 0);
    if ((qid = msgget(key, 0)) < 0)
        err_sys("open queue error");
    memset(&m, 0, sizeof(m));
    strncpy(m.mtext, argv[2], MAXMSZ-1);
    nbytes = strlen(m.mtext);
    m.mtype = 1;
    if (msgsnd(qid, &m, nbytes, 0) < 0)
        err_sys("send message");
    exit(0);
}

