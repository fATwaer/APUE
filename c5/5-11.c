#include "apue.h"
#include "stdio.h"


void pr_stdio(const char *, FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
int buffer_size(FILE *);


int 
main()
{
	FILE *fp;

	fputs("entry any character\n", stdout);
	if (getchar() == EOF)
			err_sys("getchar error");
	fputs("one line to standard error\n", stderr);
    
    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);

    if ((fp = fopen("/etc/passwd", "r")) == NULL)
        err_sys("fopen error");
    if (getc(fp) == EOF)
        err_sys("getc error");
    pr_stdio("/etc/passwd", fp);


}

void pr_stdio(const char* name, FILE *fp)
{
    printf("stream = %s", name);
	if (is_unbuffered(fp))
		printf("unbuffered");
	else if (is_linebuffered(fp))
		printf("line buffer");
	else 
		printf("fully buffered");
	printf(", buffer_size = %d\n", buffer_size(fp));
}


int 
is_unbuffered(FILE *fp)
{
    return(fp->_flag & _IO_UNBUFFERED);
}

int 
is_linebuffered(FILE *fp)
{
    return(fp->_flags & _IO_LINE_BUF);
}    

int 
buffer_size(FILE *fp)
{
#ifdef _LP64 
    return(fp->_IO_buf_end - fp->_IO_buf_base);
#else
    return(BUFSIZ);
#endif
}


