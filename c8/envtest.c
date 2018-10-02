#include <stdio.h>
#include <errno.h>
#include "apue.h"
#include <sys/time.h>
int
foo()
{
        printf("defined "
#if defined(MACOS)
        "MACOS "
#elif defined(SOLARIS)
        "SOLARIS "
#elif defined(BSD)                
        "BSD "
#elif defined(NZERO)
        "NZERO "
#elif defined(_SC_NZERO)        
        "_SC_NZERO "
#else
        "NONE"        
#endif        
        "\n");        
        return 0;
}

int
main()
{
    foo();    
}
