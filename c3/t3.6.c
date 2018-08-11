#include "apue.h"
#include <fcntl.h>

int 
main()
{
	int fd;
	char buf[1024] = {0};
	char buf2[] = "(write after seek)";
	
	if ((fd = open("file", O_RDWR)) == -1)
		err_sys("open file error");
	
	lseek(fd, 1, SEEK_SET);
	read(fd, buf, 32);
	printf("read file(seek (1)):%s\n", buf);
	
	
	lseek(fd, 1, SEEK_SET);
	write(fd, buf2, sizeof(buf2)/sizeof(*buf2));
	close(fd);
	
	exit(0);
}
