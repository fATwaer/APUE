## 15-15
    [moonlight@ArchLinux c15]$ ./a.out
    prompt>Hello, Are you my cat ?
    hello, are you my cat ?
    prompt>

## 15-31
It's a useful program to test segement.

    [moonlight@ArchLinux c15]$ ./a.out
    [global var]: 0x55afd32cd0a8
    [array[]]: 0x55afd32cd100 -> 0x55afd32d6d40
    [stack]: 0x7ffd54f3c75c
    [initialized stack_array]: 0x7ffd54f3c770 -> 0x7ffd54f463b0
    [malloced]: 0x55afd4420670 -> 0x55afd4438d10
    [shared memory]: 0x7f88a4fb9000 -> 0x7f88a4fd16a0

Q: why I declare the global and type is char variable with `static`, the global variable disappeared?
