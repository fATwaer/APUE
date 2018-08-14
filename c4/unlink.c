#include "apue.h"
#include <fcntl.h>

int
main()
{	
	if (open("tempfile", O_RDWR) < 0)
		err_sys("open error");
	if (unlink("tempfile") < 0)
		err_sys("unlink errorr");
	printf("file unlinked\n");
	
	sleep(30);
	printf("done\n");
	exit(0);
}
