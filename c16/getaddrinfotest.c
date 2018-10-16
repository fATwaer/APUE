#include "apue.h"
#include <netdb.h>
#include <sys/socket.h>

int
main(int argc, char *argv[])
{
    struct addrinfo *ailist, *aip;
    struct addrinfo hint;

    memset(&hint, 0, sizeof(hint));
    hint.ai_flags = AI_CANONNAME;
    getaddrinfo(argv[1], argv[2], &hint, &ailist);

    printf("get success!\n");
    return 0;

}
