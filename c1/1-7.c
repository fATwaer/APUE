#include "apue.h"
#include <sys/wait.h>


int
main(void)
{
	char buf[MAXLINE];
	pid_t pid;
	int status;
	
	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL) {    /*return 's' if success ,otherwise return NULL*/
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;

		if ((pid = fork()) < 0)
			err_sys("fork error .");
		else if (pid == 0) {
			execlp(buf, buf, (char *)0); /* #define NULL (void *)0*/
			err_ret("error execute");
			exit(0);
		}

		if ((pid == waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");

	
	}
	exit(0);

}
