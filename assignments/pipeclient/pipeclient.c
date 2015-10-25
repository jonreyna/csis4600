#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <linux/limits.h>
#include <string.h>
#include "../restart/restart.h"

#define FIFOARG 1

int main(int argc, char *argv[]) {
    char requestbuf[PIPE_BUF];
    int requestfd;

    if (argc != 2) { /* name of server fifo is passed on the command line */
        fprintf(stderr, "Usage: %s fifoname", argv[0]);
        return 1;
    }

    if ((requestfd = open(argv[FIFOARG], O_WRONLY)) == -1) {
        perror("Client failed to open log fifo for writing");
        return 1;
    }

    time_t curtime = time(NULL);
    snprintf(requestbuf, PIPE_BUF, "%d: %s", (int) getpid(), ctime(&curtime));
    int len = strlen(requestbuf);

    if (r_write(requestfd, requestbuf, len) != len) {
        perror("Client failed to write");
        return 1;
    }

    r_close(requestfd);

    return 0;
}