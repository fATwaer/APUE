#include "heapsort.h"
#include <stdio.h>

int 
main(int argc, char *argv[])
{
    long arr[] = {2, 5, 3, 12, 4, 10, 123, 139, 134, 123, 222, 222};
    long len = sizeof(arr)/sizeof(arr[0]);

    heapsort(arr, len);
    print_arr(arr, len);
}
