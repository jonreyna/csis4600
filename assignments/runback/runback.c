#include <stdio.h>
#include <unistd.h>

#include "../restart/restart.h"
#include "../makeargv/makeargv.h"

int main(int argc, char *argv[]) {
    pid_t childpid;
    char delim[] = " \t";
    char **myargv;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        return 1;
    }
    childpid = fork();
    if (childpid == -1) {
        perror("Failed to fork");
        return 1;
    }
    if (childpid == 0) {
        if (setsid() == -1) {
            perror("Child failed to become a session leader");
        }
        else if (makeargv(argv[1], delim, &myargv) == -1) {
            fprintf(stderr, "Child failed to construct argument array\n");
        }
        else {
            execvp(myargv[0], &myargv[0]);
            perror("Child failed to exec command");
        }
        return 1; /* child should never return */
    }
    return 0; /* parent exits */
}