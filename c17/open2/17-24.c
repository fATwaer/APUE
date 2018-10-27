#include "opend.h"

/** called by buf_args, process
 *  argv[]-style array.
 */

 int
 cli_args(int argc, char **argv)
 {
     if (argc != 3 || strcmp(argv[0], CL_OPEN) != 0) {
        strcmp(errmsg, "usage: <pathname> <oflags>\n");
        return (-1);
     }
     pathname = argv[1];
     oflag = atoi(argv[2]);
     return (0);
 }




