## 10-2

just copy

## 10-5

[] alarm

## 10-6 

the variable `n` will be copy after child process assignment. The implement of `fork()` set pages of parent process to COW(Copy On Write) meaning, after fork function calling, once one of the parent process and child process trying to write the page, a new page will be allocated to the process.so, the variable `n` won't generate confilts between parent and child.


it is a simple and interesting semaphore practice.. !:)



---
Q : read() and write() cann't do binary I/O ? 
A : read() treat the binary file as ragular file, the date that the read() get is undefined, __but__ write() can do binary I/O. In the source code `binary I/O`, it gets 

    [moonlight@ArchLinux ex]$ ./a.out
    str = �U, var = 1463126829
    str = string.., var = 1024

A struct object was writen by `write()`, and the first line prints the member of this struct reading via `read()`, but the second line is via `fread()`, this function can load a structure of C.

## 10-7 
Q: why the implement of abort() need send SIGABT twice ?

## 10-9

the type `sigset_t` cann't do shift/and/or operation, because it was implemented as struct:

``` C
typedef __sigset_t sigset_t;

#define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))
typedef struct
{
  unsigned long int __val[_SIGSET_NWORDS];
} __sigset_t;
```

when I implementing the `pr_mask()`, I cast the sitset\_t to `unsigned long int`, I don't know if the method will work(cann't cross platform?).

``` C
unsigned long int*set = (unsigned long int*)mask;
return ((*set & (1 << (signo - 1))) != 0);
```

## 10-10

    [moonlight@ArchLinux ex]$ vim 10-10.c
    [moonlight@ArchLinux ex]$ gcc 10-10.c -lapue
    [moonlight@ArchLinux ex]$ ./a.out
    time: 12:25:50 AM, Fri Oct 12, 2018
    time: 12:30:50 AM, Fri Oct 12, 2018
    time: 12:35:50 AM, Fri Oct 12, 2018
    time: 12:40:50 AM, Fri Oct 12, 2018
    time: 12:45:50 AM, Fri Oct 12, 2018
    time: 12:50:50 AM, Fri Oct 12, 2018
    time: 12:55:50 AM, Fri Oct 12, 2018
    time: 01:00:50 AM, Fri Oct 12, 2018
    time: 01:05:50 AM, Fri Oct 12, 2018
    time: 01:10:50 AM, Fri Oct 12, 2018
    time: 01:15:50 AM, Fri Oct 12, 2018
    time: 01:20:50 AM, Fri Oct 12, 2018
    time: 01:25:50 AM, Fri Oct 12, 2018
    time: 01:30:50 AM, Fri Oct 12, 2018
    time: 01:35:50 AM, Fri Oct 12, 2018
    time: 01:40:50 AM, Fri Oct 12, 2018
    time: 01:45:50 AM, Fri Oct 12, 2018
    time: 01:50:50 AM, Fri Oct 12, 2018
    time: 01:55:50 AM, Fri Oct 12, 2018
    time: 02:00:50 AM, Fri Oct 12, 2018
    time: 02:05:50 AM, Fri Oct 12, 2018
    time: 02:10:50 AM, Fri Oct 12, 2018
    time: 02:15:50 AM, Fri Oct 12, 2018
    time: 02:20:50 AM, Fri Oct 12, 2018
    time: 02:25:50 AM, Fri Oct 12, 2018
    time: 02:30:50 AM, Fri Oct 12, 2018
    time: 02:35:50 AM, Fri Oct 12, 2018
    time: 02:40:50 AM, Fri Oct 12, 2018
    time: 02:45:50 AM, Fri Oct 12, 2018
    time: 02:50:50 AM, Fri Oct 12, 2018
    time: 02:55:50 AM, Fri Oct 12, 2018
    time: 03:00:50 AM, Fri Oct 12, 2018
    time: 03:05:50 AM, Fri Oct 12, 2018
    time: 03:10:50 AM, Fri Oct 12, 2018
    time: 03:15:50 AM, Fri Oct 12, 2018
    time: 03:20:50 AM, Fri Oct 12, 2018
    time: 03:25:50 AM, Fri Oct 12, 2018
    time: 03:30:50 AM, Fri Oct 12, 2018
    time: 03:35:50 AM, Fri Oct 12, 2018
    time: 03:40:50 AM, Fri Oct 12, 2018
    time: 03:45:50 AM, Fri Oct 12, 2018
    time: 03:50:50 AM, Fri Oct 12, 2018
    time: 03:55:50 AM, Fri Oct 12, 2018
    time: 04:00:50 AM, Fri Oct 12, 2018
    time: 04:05:50 AM, Fri Oct 12, 2018
    time: 04:10:50 AM, Fri Oct 12, 2018
    time: 04:15:50 AM, Fri Oct 12, 2018
    time: 04:20:50 AM, Fri Oct 12, 2018
    time: 04:25:50 AM, Fri Oct 12, 2018
    time: 04:30:50 AM, Fri Oct 12, 2018
    time: 04:35:50 AM, Fri Oct 12, 2018
    time: 04:40:50 AM, Fri Oct 12, 2018
    time: 04:45:50 AM, Fri Oct 12, 2018
    time: 04:50:50 AM, Fri Oct 12, 2018
    time: 04:55:50 AM, Fri Oct 12, 2018
    time: 05:00:50 AM, Fri Oct 12, 2018
    time: 05:05:50 AM, Fri Oct 12, 2018
    time: 05:10:50 AM, Fri Oct 12, 2018
    time: 05:15:50 AM, Fri Oct 12, 2018
    time: 05:20:50 AM, Fri Oct 12, 2018
    time: 05:25:50 AM, Fri Oct 12, 2018
    time: 05:30:50 AM, Fri Oct 12, 2018
    time: 05:35:50 AM, Fri Oct 12, 2018
    time: 05:40:50 AM, Fri Oct 12, 2018
    time: 05:45:50 AM, Fri Oct 12, 2018
    time: 05:50:50 AM, Fri Oct 12, 2018
    time: 05:55:50 AM, Fri Oct 12, 2018
    time: 06:00:50 AM, Fri Oct 12, 2018
    time: 06:05:50 AM, Fri Oct 12, 2018
    time: 06:10:50 AM, Fri Oct 12, 2018
    time: 06:15:50 AM, Fri Oct 12, 2018
    time: 06:20:50 AM, Fri Oct 12, 2018
    time: 06:25:50 AM, Fri Oct 12, 2018
    time: 06:30:50 AM, Fri Oct 12, 2018
    time: 06:35:50 AM, Fri Oct 12, 2018
    time: 06:40:50 AM, Fri Oct 12, 2018
    time: 06:45:50 AM, Fri Oct 12, 2018
    time: 06:50:50 AM, Fri Oct 12, 2018
    time: 06:55:50 AM, Fri Oct 12, 2018
    time: 07:00:50 AM, Fri Oct 12, 2018
    time: 07:05:50 AM, Fri Oct 12, 2018
    time: 07:10:50 AM, Fri Oct 12, 2018
    time: 07:15:50 AM, Fri Oct 12, 2018
    time: 07:20:50 AM, Fri Oct 12, 2018
    time: 07:25:50 AM, Fri Oct 12, 2018
    time: 07:30:50 AM, Fri Oct 12, 2018
    time: 07:35:50 AM, Fri Oct 12, 2018



## 10-11

In the Linux 3.2.0, Mac OS X 10.6.8 Solaris, `the handler of SIGXFSZ never be called`.

use 

    dd if=/dev/null of=2M.file bs=1M count=2

to generate a disignated size file.

## 10-12

    [moonlight@ArchLinux ex]$ ./a.out 
    caught SIGALRM
    end fwrite
    [moonlight@ArchLinux ex]$ ll -h BIG.file 
    -rw-r--r-- 1 moonlight users 1.0G Oct 12 00:04 BIG.file

Practically, I waited for a while, the `fwrite()` may have written 1G file before process handler.

