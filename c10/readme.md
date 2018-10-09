## 10-2

    ./a.out &
    $ kill -USR1 pid
    $ kill -USR2 pid
    $ kill pid

## sigchld
1).\_exit(0)

    [moonlight@ArchLinux c10]$ ps -o pid,ppid,comm
      PID  PPID COMMAND
     1512  1333 bash
     1569  1512 a.out
     1570  1569 a.out <defunct>
     1575  1512 ps

2). exit(0)

    [moonlight@ArchLinux c10]$ ps -o pid,ppid,comm
      PID  PPID COMMAND
     1512  1333 bash
     1599  1512 a.out
     1600  1599 a.out <defunct>
     1603  1512 ps

3). wait(NULL)
before child become zombie process

    [moonlight@ArchLinux c10]$ ps -o pid,ppid,comm
      PID  PPID COMMAND
     1512  1333 bash
     1939  1512 a.out
     1942  1512 ps

4). after
 
same as before 

## 10-9.c

- loop time

        [moonlight@ArchLinux c10]$ time ./a.out

        real	0m11.516s
        user	0m11.508s
        sys	0m0.000s



- sleep time < loop time

        [moonlight@ArchLinux c10]$ ./a.out 
        ^C
        sig\_int handler starting
        sleep2 returned 0

alarm signal interupts the sig\_int handler.

- sleep time > loop time

        [moonlight@ArchLinux c10]$ ./a.out
        ^C
        sig\_int handler starting
        sig\_int handler finished
        sleep2 returned 7

    Q: ? after sig\_int handler returned, it activates the pause() func? , and than the sleep2() returns;



     


