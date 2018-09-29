#include "apue.h"
#include <sys/resource.h>

int
main(int argc, char **argv)
{
    int var = 0;
    int var2 = 0;
    printf("main: %p\n", main);
    printf("argv: %p\n", argv);

    for (int i = 0; i < argc; i++)
        printf("argv[%d]: %p\n", i, argv[i]);

    printf("var: %p\n", &var);
    printf("var2: %p\n", &var2);
    printf("argc: %p\n", &argc);
}
