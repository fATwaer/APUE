## 12-13

    [moonlight@ArchLinux c12]$ ./a.out
    thread 139710660527872
    PATH = /usr/local/bin:/usr/local/sbin:/usr/bin:/usr/lib/jvm/default/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl
    calling deconstruction ..
    thread 139710652135168
    PATH = /usr/local/bin:/usr/local/sbin:/usr/bin:/usr/lib/jvm/default/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl
    calling deconstruction ..
    [moonlight@ArchLinux c12]$



## 12-16

    [moonlight@ArchLinux c12]$ ./a.out 
    ^C^C
    thread(140626976249600) received interrupt
    ^C
    thread(140626976249600) received interrupt
    ^C
    thread(140626976249600) received interrupt
    ^\
    thread(140626976249600) received quit 
    [moonlight@ArchLinux c12]$ 


## 12-17

    [moonlight@ArchLinux c12]$ ./a.out
    thread started...
    about to fork ...
    preparing locks...
    parent unlocking locks...
    parent returned from fork
    child unlocking locks...
    child returned from fork

the order registering on `pthread_atfork()` is opposite calling order.
