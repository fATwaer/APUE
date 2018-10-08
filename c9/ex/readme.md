    [moonlight@ArchLinux ex]$ ./a.out 
    parent: pid = 5192, ppid = 3405, pgrp = 5192, sid = 3405, tpgrp = 5192
    child: pid = 5193, ppid = 5192, pgrp = 5192, sid = 3405, tpgrp = 5192
    new pg: pid = 5193, ppid = 5192, pgrp = 5193, sid = 5193, tpgrp = -1

according to the value of `sid` and `pgrp`, this child process become a seesion leader and process group leader. The leader process don't have console terminal because calling `tcgetpgrp()` returns -1 , and prints "tggrp = -1".
