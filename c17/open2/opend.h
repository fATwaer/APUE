#include "apue.h"
#include <errno.h>

#define CS_OPEN "/tmp/opend.socket"
#define CL_OPEN "open"

extern int debug;
extern char errmsg[];
extern int oflag;
extern char *pathname;

typedef struct {
    int     fd;
    uid_t   uid;
}Client;

extern Client *client;
extern int    client_size;

int cli_args(int, char **);
int client_add(int, uid_t);
void client_del(int);
void loop(void);
void handle_request(char *, int, int, uid_t);
