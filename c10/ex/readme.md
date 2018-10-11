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


