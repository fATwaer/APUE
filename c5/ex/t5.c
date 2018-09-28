#include "apue.h"

int
my_setbuf(FILE *fp, char *buf)
{
    setvbuf(fp, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
}

int
main()
{
    char buf[] = "it does not hurt me";
    FILE* fp;
    int fd;

    if ((fp = fopen("./ex.file", "w+")) == NULL)
        err_sys("fopen file failed");

    fd = fileno(fp);
    fputs(buf, fp);

    fflush(fp);
    while (fsync(fd) != 0);

    printf("access success !\n");
}
