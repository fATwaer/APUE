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

(done! see ex11.2)

## 11-16

It is insteresting program ! :)))

I rewrite the heap-sort code, because i think the interface is hard to use. So, I rewrited like below:

    void *heapsort(void * addr, size_t length);

To gain more information, you can see `lib/heapsort.*`.

- compile

        gcc 11-16.c -Ilib/ lib/heapsort.c -lapue -lpthread -DDEBUG=1 -g

- result

        [moonlight@ArchLinux c11]$ ./a.out 
        thread(140236969490176) sort:1804289383 846930886   ... ...   2025884438 429357853 
        thread(140236952704768) sort:286087516 1268898063   ... ...   1936732637 1345329787 
        thread(140236961097472) sort:771126689 1697371363   ... ...   800325282 925758837 
        thread(140236944312064) sort:411590671 1047810025   ... ...   365897492 1672400060 
        thread(140236935919360) sort:48523469 614983990   ... ...   895300851 767147961 
        thread(140236927526656) sort:918014249 830351765   ... ...   768393037 951493745 
        thread(140236919133952) sort:553194019 1800398203   ... ...   905686412 123436433 
        thread(140236910741248) sort:501824108 1038027565   ... ...   1598025017 1759479965 
        thread(140236919133952) sorted:2218 7368 8146 12325   ... ...   2147476086 2147481154 2147481509 2147481902 
        thread(140236969490176) sorted:1210 3722 4686 5712   ... ...   2147471385 2147476900 2147477011 2147480021 
        thread(140236927526656) sorted:5643 9956 11656 11835   ... ...   2147476269 2147476372 2147478113 2147480511 
        thread(140236952704768) sorted:880 2333 8205 10014   ... ...   2147470831 2147471975 2147478292 2147481194 
        thread(140236935919360) sorted:37 2172 4562 6330   ... ...   2147467437 2147475042 2147481500 2147482567 
        thread(140236961097472) sorted:2126 2552 4125 4855   ... ...   2147474987 2147477294 2147479638 2147481384 
        thread(140236910741248) sorted:7718 12136 18514 20308   ... ...   2147481456 2147482312 2147482459 2147483025 
        thread(140236944312064) sorted:614 858 2508 7091   ... ...   2147470497 2147476105 2147478980 2147479881 
        sort took    2 seconds
        37 614 858 880 1210    ... ...    2147481902 2147482312 2147482459 2147482567 2147483025 
        [moonlight@ArchLinux c11]$ 


