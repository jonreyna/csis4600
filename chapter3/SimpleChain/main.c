#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s processes\n", argv[0]);
        return 1;
    }

    pid_t childpid = 0;
    int n = atoi(argv[1]), i;
    for (i = 1; i < n; ++i) {
        if (childpid = fork())
            break;
    }

    fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
            i, (long) getpid(), (long) getppid(), (long) childpid);

    return 0;
}