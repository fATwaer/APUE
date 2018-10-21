#include <syslog.h>

int 
main()
{
    syslog(LOG_ERR, "APUE LOG ERROR");
}

