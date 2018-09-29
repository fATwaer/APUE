#include "stdio.h"
#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *
getpwnam(const char *name)
{
    struct passwd *ptr;

    setpwent();
    while ((ptr = getpwent()) != NULL)
        if (strcmp(ptr->pw_name, name))
            break;
    endpwent();
    return (ptr);
}

int
main()
{
    struct passwd *p = getpwnam("moonlight");

    printf("passwd: %s dir: %s\n", p->pw_passwd, p->pw_dir);
}
