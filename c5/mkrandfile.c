#include "apue.h"
#include "errno.h"

void
make_temp(char *name_template)
{
    int fd;
    struct stat sbuf;

    if ((fd = mkstemp(name_template)) < 0)
        err_sys("mkstemp error");
    printf("template name = %s\n", name_template);

    if (stat(name_template, &sbuf) < 0) {
        if (errno == ENOENT)
            printf("file doesn't exit\n");
        else
            err_sys("stat failed");
    } else {
        printf("file exists\n");
        unlink(name_template);
    }
}


int
main()
{
    char good_template[] = "/tmp/mydirXXXXXX";
    char *bad_template = "/tmp/mydirXXXXXX";

    printf("trying to create first temp file ... \n");
    make_temp(good_template);
    printf("trying to create second temp file ... \n");
    make_temp(bad_template);
    exit(0);
}
