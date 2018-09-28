#include "apue.h"

#define BSZ 48

int main()
{
    FILE *fp;
    char buf[BSZ];

    memset(buf, 0, BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X' ;
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
        printf("fmemopen error");
    printf("initial buffer contents %s\n", buf);

    fprintf(fp, "1234567");
    printf("before flush: %s\n", buf);
    fflush(fp);
    printf("after flush: %s\n", buf);
    printf("length of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'b', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X' ;
    fprintf(fp, "1234567");
    fseek(fp, 0, SEEK_SET);
    printf("after fseek %s\n", buf);
    printf("length of string in buf = %ld\n", (long)strlen(buf));


    memset(buf, 'c', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp, "1234567");
    fclose(fp);
    printf("after fclose:%s\n", buf);
    printf("length of string inbuf = %ld\n", (long)strlen(buf));
}
