#include "apue.h"
#include <fcntl.h>

int
main()
{
	int fd = open("/dev/fd/0", O_WRONLY);
	write(fd, "abcd\n", 5);
	exit(0);
}

