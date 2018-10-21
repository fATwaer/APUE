#include "apue.h"
#include <netdb.h>
#include <sys/socket.h>

void
pr_stat(struct stat *sstat)
{
    if (!S_ISSOCK(sstat->st_mode))
        err_sys("not socket");
    printf("sockfd:\n");
    printf(" i-node number = %d\n", sstat->st_ino);
    printf(" device number = %d\n", sstat->st_dev);
    printf(" device number(special files) = %d\n", sstat->st_rdev);
    printf(" number of links = %d\n", sstat->st_nlink);
    printf(" owner userID = %d\n", sstat->st_uid);
    printf(" groupID = %d\n", sstat->st_gid);
    printf(" file size = %d\n", sstat->st_size);
    printf(" last access = %d\n", sstat->st_atim.tv_sec);
    printf(" last modification = %d\n", sstat->st_mtim.tv_sec);
    printf(" last file status change = %d\n", sstat->st_ctim.tv_sec);
    printf(" best I/O block size = %d\n", sstat->st_blksize);
    printf(" allocated block = %d\n", sstat->st_blocks);
}


int
main()
{
    struct stat     sstat;
    int             sockfd;
    struct addrinfo hint;
    struct addrinfo *aip, *ailist;

    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

    if (getaddrinfo("ArchLinux", "ruptime", &hint, &ailist) < 0)
        err_sys("getaddrinfo error");
    for (aip = ailist; aip != NULL; aip = aip->ai_next) {
        if ((sockfd = socket(aip->ai_family, SOCK_STREAM, aip->ai_protocol)) < 0)
            err_sys("getaddrinfo error");
        if (fstat(sockfd, &sstat) < 0)
            err_sys("fstat error");
        pr_stat(&sstat);
    }



    exit(0);
}


