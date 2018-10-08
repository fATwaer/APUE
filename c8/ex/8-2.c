#include "apue.h"
#include <sys/types.h>
#include <unistd.h>

static pid_t pid;

void
f1()
{
    printf("here is f1\n");

    //TELL_WAIT();
    if ((pid = vfork()) < 0)
        err_sys("vfork error");
    else if (pid == 0) { //child
        printf("child return\n");
        return;
    } else {
        printf("parent return\n");
        return;
    }
}

int
f2()
{
    if (pid == 0) {
        printf("arrived f2, telling parent...\n");
        _exit(0);
    }

    if (pid > 0) {
        printf("here is f2 in parent\n");
        //TELL_CHILD(pid);
    }
}


int
main()
{
    f1();

    printf("%s return from f1() \n", pid > 0 ? "parent": "child");

    f2();

    printf("end of main\n");
    exit(0);
}

