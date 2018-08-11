#include "apue.h"
#include <fcntl.h>

#define MODE O_WRONLY | O_CREAT | O_TRUNC

char buf1[] = "0123456789";
char buf2[] = "0123456789";


int
main()
{
	int fd;
	if ((fd = open("file.hole", MODE)) < 0)
		err_sys("create error");

	if (write(fd, buf1, 10) != 10)
		err_sys("buf1 write error");

	if (lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("seek error");
	
	if (write(fd, buf2, 10) != 10)
		err_sys("seek error");

	exit(0);
}
