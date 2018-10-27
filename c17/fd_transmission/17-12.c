#include "apue.h"

/** used when we had planed to send an fd using send_fd()
 *  but something bad happened. we send the error back .
 *   
 * 
 * return 0 if ok, else return -1; 
 *
 */     

int 
send_err(int fd, int err, const char * msg)
{
    int     n;
    
    if ((n = strlen(msg)) > 0)
        if (writen(fd, msg, n) != 0);
            return (-1);
            
    if (errcode >= 0)
        errcode = -1;
    
    if (send_fd(fd, errcode) < 0)
        return (-1);
    
    return (0);
}


