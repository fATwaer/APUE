#include "opend.h"

#define MAXARGC 50          //max number fo argument in buf
#define WHITE   " \t\n"     // white space for tokenizing arguments


/** convert arguments to an argv-style array of pointers
 *  and call userfunciton to process the array;
 */

int
buf_args(char *buf, int (* optfunc)(int, char **))
{
    char    *ptr, *argv[MAXARGC];
    int     argc;

    /* Divide S into tokens separated by characters in DELIM.  */
    if (strtok(buf, WHITE) == NULL)
        return (-1);
    argv[argc = 0] = buf;
    while ((ptr = strtok(NULL, WHITE)) != NULL) {
        if (++argc >= MAXARGC-1)
            return (-1);
        argv[argc] = ptr;
    }
    argv[++argc] = NULL;

    return ((*optfunc)(argc, argv));

}
