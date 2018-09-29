#include "apue.h"
#include <fcntl.h>

int
main(int argc, char *argv[])
{
	int fd = 0;
	char buf1[] = "abcdefg";
	char buf2[] = "ABCDEFG";
	off_t off = 65536;
	size_t memsz = off + strlen(buf1) + strlen(buf2);
	char* buf3 =(char*) malloc(memsz);

	memset(buf3, 32, memsz);

	/*hole file*/
	if ((fd = open("file.hole", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) < 0)
		err_sys("error open");
	int n = strlen(buf1);
	if (write(fd, buf1, n) != n)
		err_sys("error write buf1");
	if (lseek(fd, off, SEEK_CUR) < 0)
		err_sys("error seek");
	n = strlen(buf2);
	if (write(fd, buf2, n) != n)
		err_sys("error write buf2");
	close(fd);

	/*nohole file*/
	if ((fd = open("file.nohole", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) < 0)
		err_sys("error open");
	if (write(fd, buf3, memsz) != memsz)
		err_sys("error write buf3");
	free(buf3);
	close(fd);

	exit(0);


}
