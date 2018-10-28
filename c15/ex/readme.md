## 15-4

    [moonlight@ArchLinux ex]$ ps
      PID TTY          TIME CMD
     3496 pts/0    00:00:00 bash
     4328 pts/0    00:00:00 15-4
     4329 pts/0    00:00:00 add2
     4333 pts/0    00:00:00 ps
    [moonlight@ArchLinux ex]$ kill 4329
    [moonlight@ArchLinux ex]$ fg
    ./15-4
    [moonlight@ArchLinux ex]$
    [moonlight@ArchLinux ex]$
    [moonlight@ArchLinux ex]$ echo $?
    141
    [moonlight@ArchLinux ex]$


i got 141 here. it may be made up of 128 and 13. blow it is definenation of SIGPIPE.

    #define	SIGPIPE		13	/* Broken pipe.  */

## 15-13

I reused the picture 15-18 mapping shared memory supplied by the XSI. my test program (15.13) is going to map  a memory area and store linklist datastrcture, and the program(15.13.2) is going to parse the content from the shared memeory.

    [moonlight@ArchLinux ex]$ ./a.out
    [global var]: 0x56537c6790c0
    [array[]]: 0x56537c679120 -> 0x56537c682d60
    [stack]: 0x7ffdf6a8af54
    [initialized stack_array]: 0x7ffdf6a8af60 -> 0x7ffdf6a94ba0
    [malloced]: 0x56537c74e670 -> 0x56537c766d10
    [shared memory]: 0x7fee10f7c000 -> 0x7fee10f946a0
    id 753673
    id = 1, data = 'ikbc'
    id = 2, data = 'codeblock'
    id = 3, data = 'be quiet!'

    [moonlight@ArchLinux ex]$ ./an
    [shared memory]: 0x7f0e2312a000 -> 0x7f0e231426a0
    id = 1, data = 'ikbc'
    id = 2, data = 'codeblock'
    id = 3, data = 'be quiet!'
