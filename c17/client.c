#include "apue.h"
#include <stdio.h>


extern int cli_conn(const char *name);
extern int recv_fd(int i,ssize_t (*username)(int, const void *, size_t));
ssize_t
userfunction(int fileno, const void * addr, long unsigned int n)
{
    if (write(fileno, addr, n) != n)
        err_sys("write error");
    
    return (0);
}


int 
main()
{
    int clfd;
    int newfd;
    struct stat stat;
    if ((clfd = cli_conn("UNIX.socket")) < 0)
        err_sys("error");
    else
        printf("connect established, receiving fd..\n");

    newfd = recv_fd(clfd, userfunction);
    printf("new fd is %d\n", newfd);
    write(newfd, "a fd is passed by the recv(fd)\0", 20);
}
