#include "apue.h"

int
main(void)
{
	int c;
	
	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
			err_sys("write error !");

	if (ferror(stdin))
		err_sys("getc() error");

	exit(0);
			
}
