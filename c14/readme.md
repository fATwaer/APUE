## 14-12
    [moonlight@ArchLinux c14]$ ./a.out mandatory.file
    read_lock of already_locked region returns 11
    read OK(no mandatory locking), buf = ab

## 14-21
    [moonlight@ArchLinux c14]$ gcc 14-21.c -lapue -lrt
    [moonlight@ArchLinux c14]$ ./a.out  input.file  out.file
    buf[0] unused->read_pending
    buf[1] unused->read_pending
    buf[2] unused->read_pending
    buf[3] unused->read_pending
    buf[4] unused->read_pending
    buf[5] unused->read_pending
    buf[6] unused->read_pending
    buf[7] unused->read_pending
    buf[0] read_pending->write_pending
    buf[1] read_pending->write_pending
    buf[2] read_pending->write_pending
    buf[3] read_pending->write_pending
    buf[4] read_pending->write_pending
    buf[5] read_pending->write_pending
    buf[6] read_pending->write_pending
    buf[7] read_pending->write_pending
    buf[0] write_pending->unused
    buf[1] write_pending->unused
    buf[2] write_pending->unused
    buf[3] write_pending->unused
    buf[4] write_pending->unused
    buf[5] write_pending->unused
    buf[6] write_pending->unused
    buf[7] write_pending->unused
    buf[0] unused->read_pending
    buf[1] unused->read_pending
    buf[0] read_pending->write_pending
    buf[1] read_pending->write_pending
    buf[0] write_pending->unused
    buf[1] write_pending->unused

