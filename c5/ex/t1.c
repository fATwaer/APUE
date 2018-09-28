#include "apue.h"

int
my_setbuf(FILE *fp, char *buf)
{
    setvbuf(fp, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
}

int
main()
{
    FILE *fp;
    char c;
    char buf[BUFSIZ];

    my_setbuf(stdout, NULL);

    for (int i = 0; i < 10; i++)
    {
        printf("hahah\n");
        sleep(1);
    }


    //fflush(stdout);

}
