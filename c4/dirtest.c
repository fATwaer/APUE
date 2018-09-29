#include "apue.h"
#include <dirent.h>
#include <fcntl.h>


int
main(int argc, char *argv[])
{	
	struct stat statbuf;
		
	lstat(argv[1], &statbuf);
	if (S_ISDIR(statbuf.st_mode) == 0)
		printf("not dir: %d\n", statbuf.st_mode);
	else
		printf("unknown\n");
}
