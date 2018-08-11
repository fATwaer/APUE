#include "apue.h"
#include <fcntl.h>

int
main()
{
	int fd1, fd2;
	int off1, off2, off3;
	char buf[32] = {0};

	fd1 = open("file", O_RDONLY);
	fd2 = open("file", O_RDONLY);

	read(fd1, buf, 3);
	off1 = lseek(fd1, 0, SEEK_CUR);
	printf("read: %s\n", buf);
	
	read(fd2, buf, 5);
	off2 = lseek(fd2, 0, SEEK_CUR);
	
	int fd3 = dup(fd1);
	off3 = lseek(fd3, 0, SEEK_CUR);


	printf("read: %s\n", buf);
	printf("fd1 off: %d, fd2 off: %d, fd3 off:%d\n ", off1, off2, off3);

	exit(0);
}
