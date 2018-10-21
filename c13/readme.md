## 13-1

    [moonlight@ArchLinux c13]$ ps -efj  | grep 752
    moonlig+   752     1   752   752  0 17:55 ?        00:00:00 /usr/lib/systemd/systemd --user
    moonlig+   998   752   998   998  0 17:55 ?        00:00:00 /usr/lib/evolution-calendar-factory
    moonlig+  3546   752  3546  3546  0 20:02 ?        00:00:10 /usr/lib/gnome-terminal/gnome-terminal-server
    moonlig+  3838   752  3837  3837  0 20:20 ?        00:00:00 ./a.out
    moonlig+  3844  3554  3843  3554  0 20:20 pts/2    00:00:00 grep 752

archlinux has a little difference from normal linux, it use systemd to insist of init process.
AND, archlinux could check the log information by type:

    journalctl -p err --since "time"

and output:

    [moonlight@ArchLinux c13]$ journalctl -p err --since "20 min ago"
    Hint: You are currently not seeing messages from other users and the system.
          Users in groups 'adm', 'systemd-journal', 'wheel' can see all messages.
          Pass -q to turn off this notice.
    -- Logs begin at Mon 2018-08-20 11:51:12 CST, end at Sun 2018-10-21 20:54:33 CST. --
    Oct 21 20:54:33 ArchLinux a.out[4128]: APUE LOG ERROR



## 13-7

    moonlig+  2761   751  2760  2760  0 23:02 ?        00:00:00 ./a.out
    root      2763     2     0     0  0 23:02 ?        00:00:00 [kworker/5:2]
    moonlig+  2764  2611  2764  2611  0 23:03 pts/2    00:00:00 ps -efj
    [moonlight@ArchLinux c13]$ 

the program has daemonized successfully, and send SIGHUP signal to this daemon.

    [moonlight@ArchLinux c13]$ journalctl -p 3 --since "3 min ago"
    Hint: You are currently not seeing messages from other users and the system.
          Users in groups 'adm', 'systemd-journal', 'wheel' can see all messages.
          Pass -q to turn off this notice.
    -- Logs begin at Wed 2018-10-10 20:17:23 CST, end at Sun 2018-10-21 23:04:27 CS>
    Oct 21 23:04:00 ArchLinux a.out[2761]: Re-reading configuration file
    Oct 21 23:04:01 ArchLinux a.out[2761]: Re-reading configuration file
    Oct 21 23:04:13 ArchLinux a.out[2761]: got SIGTERM; exiting

for convenience, I change the log priority from `LOG_INFO` to `LOG_ERR`.


