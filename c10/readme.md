## 10-2

    ./a.out &
    $ kill -USR1 pid
    $ kill -USR2 pid
    $ kill pid

be careful with the function signal(), it just push the handler function into the process stack. after catching the signal and calling the handler, the handler function pointer will be `pop` out.


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

## 10-9

- loop time

        [moonlight@ArchLinux c10]$ time ./a.out

        real	0m11.516s
        user	0m11.508s
        sys	0m0.000s



- sleep time < loop time

        [moonlight@ArchLinux c10]$ ./a.out 
        ^C
        sig_int handler starting
        sleep2 returned 0

alarm signal interupts the sig\_int handler.

- sleep time > loop time

        [moonlight@ArchLinux c10]$ ./a.out
        ^C
        sig_int handler starting
        sig_int handler finished
        sleep2 returned 7

    Q: ? after sig\_int handler returned, it activates the `pause()` func? , and than the `sleep2()` returns;


# 10-15

    [moonlight@ArchLinux c10]$ ./a.out 
    ^\^\^\^\
    SIGQUIT pending
    caught SIGQUIT
    SIGQUIT unblocked
    ^\Quit (core dumped)
    [moonlight@ArchLinux c10]$
     
# 10-20

- sigsetjump version
     
        [moonlight@ArchLinux c10]$ ./a.out  &
        [1] 5968
        [moonlight@ArchLinux c10]$ starting main: 
        kill -USR1 5968
        starting sig_usr1:  SIGUSR1
        [moonlight@ArchLinux c10]$ in sig_alarm:  SIGUSR1 SIGALRM
        finishing sig_usr1:  SIGUSR1
        ending main: 

        [1]+  Done                    ./a.out

- setjump version
        
        [moonlight@ArchLinux c10]$ ./a.out  &
        [1] 6178
        [moonlight@ArchLinux c10]$ starting main:
        kill -USR1 6178
        starting sig_usr1:  SIGUSR1
        [moonlight@ArchLinux c10]$ in sig_alarm:  SIGUSR1 SIGALRM
        finishing sig_usr1:  SIGUSR1
        ending main:  SIGUSR1

        [1]+  Done                    ./a.out

when the signal arrived, the new comming signal is masked automaticly before calling handler. when the handler returns, this signal will be removed from the mask list. but before the `setjump` version program returning, it called `longjmp` and don't recover the mask list, the `SIGUSR1` is still blocked.

## 10-22

__sigsuspend:__ set mask signal & pause

    [moonlight@ArchLinux c10]$ ./a.out
    program start:
    critical region SIGINT
    ^C
    in sig_int:  SIGUSR1
    after return from sigsuspend:  SIGINT
    program exit: 

## 10-23

    [moonlight@ArchLinux c10]$ ./a.out
    ^C
    Interrupt
    ^C
    Interrupt
    ^\[moonlight@ArchLinux c10]$

* use 10-18 signal() function 


## 10-28

    [moonlight@ArchLinux c10]$ ./a.out 
    execute sh...
    q
    before reset mask
    caught SIGCHLD
    system return
    [moonlight@ArchLinux c10]$ 

SIGCHLD was blocked before reset mask via `sigprocmask()`, and called handled between reseting mask and system() returning.

be careful,
``` C
while (waitpid(pid, &status, 0) < 0)
if (errno != EINTR) {
    status = -1;
    break;
}
```

`waitpid()` returned -1 when the child of the parent process all terminated , and the `for` loop was going to breaking.

## 10-31

    [moonlight@ArchLinux c10]$ ./a.out
    studio Don Juan
    studio Don Juan
    ^Zsuspend and back to terminal
    waiting SIGCONT ....

    [2]+  Stopped                 ./a.out
    [moonlight@ArchLinux c10]$ fg 2
    ./a.out
    proc continue executing


    [moonlight@ArchLinux c10]$

`"when the signal arrived, the new comming signal is masked automaticly before calling handler."`

