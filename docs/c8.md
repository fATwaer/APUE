    ps -o pid,ppid,pgid,sid,tgid,comm | cat1 | cat2

pgid : process group id
sid  : session id
tpgid : t pgid
comm : command


## 9-12

    [moonlight@ArchLinux c9]$ ./a.out 
    parent: pid = 4584, ppid = 3405, pgrp = 4584, tpgrp = 4584
    child: pid = 4585, ppid = 4584, pgrp = 4584, tpgrp = 4584
    SIGHUP received, pid = 4585
    child: pid = 4585, ppid = 739, pgrp = 4584, tpgrp = 3405
    read error 5 on controlling tty
    [moonlight@ArchLinux c9]$ ps 739
        PID TTY      STAT   TIME COMMAND
        739 ?        Ss     0:00 /usr/lib/systemd/systemd --user

systemd is one of init program, meaning the new parent of orphan process is init process.
