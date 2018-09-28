#include "stdio.h"

#if defined(_IO_UNBUFFERD)
int foo()
{
    printf("_IO_UNBUFFERD\n");
}
#elif defined(__SNBF)
int foo()
{
    printf("__SNBF\n");
}
#elif defined(_IONBF) 
int foo()
{
    printf("_IONBF\n");
#ifdef _LP64
    printf("defined _LP64\n");
#endif

}
#endif

int main()
{
    printf("marco: ") ;
    foo();
}
