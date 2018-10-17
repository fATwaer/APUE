## 16-16 && 16-17

- compile

    gcc 16-10.c 16-16.c -lapue -o client -g -Werror
    gcc 16-12.c 16-17.c -lapue -o server -g -Werror

- not supported

when compiled this source file, syslog record this fault.

    Servname not supported for ai_socktype

To solve the problem, add this line into `/etc/services`, allocate a port for the this service `ruptime`.
![/etc/services](https://github.com/fATwaer/APUE/tree/master/docs/pic/service.png)

- can't connect 

use `hostname` not `localhost`

if don't know the hostname, just print the hostname after 16-17 called the `gethostname()`.

![ruptime](https://github.com/fATwaer/APUE/tree/master/docs/pic/ruptime.png)
