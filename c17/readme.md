## 17-3,4

    [moonlight@ArchLinux c17]$ ./sendmsg 0x123 "hello,word"
    [moonlight@ArchLinux c17]$ ./pollmsg &
    [1] 3056
    [moonlight@ArchLinux c17]$ queue ID 0 is 65538
    queue ID 1 is 0
    queue ID 2 is 98307
    queue id 65538, message hello,word

    [moonlight@ArchLinux c17]$ ./sendmsg 0x123 "xsi message"
    queue id 65538, message xsi message
    [moonlight@ArchLinux c17]$ ./sendmsg 0x124 "just a test"
    queue id 0, message just a test
    [moonlight@ArchLinux c17]$ ./sendmsg 0x125 "bye"
    queue id 98307, message bye
    [moonlight@ArchLinux c17]$ ./sendmsg 0x125 "bye";./sendmsg 0x125 "bye";\
    > ./sendmsg 0x123 "bye"; ./sendmsg 0x124 "bye"
    queue id 98307, message bye
    queue id 98307, message bye
    queue id 65538, message bye
    queue id 0, message bye
    [moonlight@ArchLinux c17]$

