#include "apue.h"
//#ifdef SOLARIS
#include <sys/types.h>
#include <sys/sysmacros.h>
//#endif

int
main(int argc, char *argv[])
{
	int i;
	struct stat statbuf;
	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		if (stat(argv[i], &statbuf) < 0) {
			err_ret("stat error");
			continue;
		} 
		printf("dev = %d/%d", major(statbuf.st_dev), minor(statbuf.st_dev));
		if (S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode)) {
			printf("(%s) rdev %d/%d", 
			S_ISBLK(statbuf.st_mode) ? "block" : "character",
			major(statbuf.st_rdev), minor(statbuf.st_rdev) );
		}
		printf("\n");
	}
	exit(0);
}
