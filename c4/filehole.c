#include "apue.h"
#include <fcntl.h>


int
main()
{
	int fd;
	fd = open("core", O_RDWR | O_CREAT);
	
	write(fd, "1234", 4);
	
	lseek(fd, 4096, SEEK_SET);
	write(fd, "1234", 4);

	exit(0);
}
