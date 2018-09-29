#include "apue.h"
#include <sys/resource.h>


#define doit(name) pr_limits(#name, name)

#define test(abc) foo(#abc)


static void foo(char *);


static void pr_limits(char *, int);






int
main()
{
    doit(RLIMIT_CORE);
    return 0;
}


static void pr_limits(char *name, int resource)
{
    struct rlimit limit;
    unsigned long long lim;

    if (getrlimit(resource, &limit) < 0)
        err_sys("getrlimit error for %s", name);
    printf("%-14s  ", name);

    if (limit.rlim_cur == RLIM_INFINITY) {
        printf("(infinite)");
    } else {
        lim = limit.rlim_cur;
        printf("%10lld", lim);
    }
    if (limit.rlim_max == RLIM_INFINITY) {
        printf("(infinite)");
    } else {
        lim = limit.rlim_max;
        printf("%10lld", lim);
    }
    putchar((int)'\n');
}




static void
foo(char *str)
{
    printf("%s\n", str);
}
