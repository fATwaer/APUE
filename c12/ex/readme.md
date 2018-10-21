## 12-1

    [moonlight@ArchLinux c12]$ ./a.out > ex/12-1.output
    [moonlight@ArchLinux c12]$ cat ex/12-1.output
    thread started...
    about to fork ...
    preparing locks...
    parent unlocking locks...
    parent returned from fork
    thread started...
    about to fork ...
    preparing locks...
    child unlocking locks...
    child returned from fork

when redirected the output to file, the process become full-buffered, but terminal is line-buffered.it can be normal by adding `setbuf(stdout, NULL)`.

    [moonlight@ArchLinux c12]$ cat ex/12-1.output
    thread started...
    about to fork ...
    preparing locks...
    parent unlocking locks...
    parent returned from fork
    child unlocking locks...
    child returned from fork

because of full-buffer, process will flush the buffer at closing this file.
so when calling the `fork`,both parent and child got a copy of the buffer.

## 12-2

just block all signal.

    [moonlight@ArchLinux ex]$ ./a.out
    mememe:yoyoyo
    /usr/local/bin:/usr/local/sbin:/usr/bin:/usr/lib/jvm/default/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl:/local/random


## 12-3

be careful the case in 11-2: when blocking all signal and processing, it may call some function that reset the mask to unblock signal. it's not asynchronously sigal-safe.

## 12-6

I don't know how to do it.

## 12-8

i think it needn't calculate the remain time. If passing a nagtive value to `clock_nanosleep()`, the function will return immediately.


