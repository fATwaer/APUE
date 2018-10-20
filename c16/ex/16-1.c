#include <stdio.h>


int 
main()
{
    unsigned int bit = 0x12345678;  // 4bytes
    char *ptr = &bit;
    int i;

    printf("%#x\n", bit);
    for (i = 0; i < 4; i++) {
        printf("%p -> %x\n", ptr, *ptr);
        ptr += 1;
    }
    
}
