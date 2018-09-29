#include "apue.h"
#include <fcntl.h>
#define BFSZ 4096

int 
main(int argc, char *argv[])
{	
	int fd1, fd2;
	int n;
	char buf[BFSZ];

	if (argc != 3)
		err_sys("usage: cp file1 file2");

	if ((fd1 = open(argv[1], O_RDONLY)) < 0)
		err_sys("open file error :%s", argv[1]);
	if ((fd2 = open(argv[2], O_RDWR|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR)) < 0)
		err_sys("open file error :%s", argv[2]);

	while ((n = read(fd1, buf, BFSZ)) != 0) {
		if (write(fd2, buf, n) != n)
			err_sys("write error");	
	}

	exit(0);
}
