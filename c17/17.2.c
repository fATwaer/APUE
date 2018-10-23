#include <apue.h>
#include "sys/socket.h"

int 
{
    return (socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}
