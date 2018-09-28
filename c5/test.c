#include "apue.h"

int
main()
{
	float data[10] = {1.2};
	FILE* fp = fopen("foo", "a+");
	
	if (fwrite(&data[2], sizeof(float), 4, fp) != 4);
		err_sys("fwrite error");
}
