## 11-4

- return ver

        [moonlight@ArchLinux c11]$ gcc 11-4.c -lapue -lpthread -Werror
        11-4.c: In function ‘thr_fn1’:
        11-4.c:26:13: error: function returns address of local variable [-Werror=return-local-addr]
             return ((void *)&foo);
                    ~^~~~~~~~~~~~~
        cc1: all warnings being treated as errors

we cann't compile the source file, because `struct foo b` is a local variable, so here we should call `pthread_exit()`.

    pthread_exit((void *)&foo);

support exception exit, but `return` not.

- exit ver


        [moonlight@ArchLinux c11]$ ./a.out 
        thread 1:
         sturcture at 0x3a701ed0
         foo.a = 1
         foo.b = 2
         foo.c = 3
         foo.d = 4
        second thread..
        thread 2 ID = 139909540095744
        parent:
         sturcture at 0x3a701ed0
         foo.a = 12
         foo.b = 0
         foo.c = 981610490
         foo.d = 32575

thread 1 __overwrite__ the stack of thread 1.




## 11-11
`coarse-grained`

## 11-13

    [moonlight@ArchLinux c11]$ ./a.out
    mutex is locked
    current time is 10:12:13 PM
    the time is now 10:12:23 PM
    can't lock mvtex again:Connection timed out


## 11-14

I don't know how to use these job queue... 
