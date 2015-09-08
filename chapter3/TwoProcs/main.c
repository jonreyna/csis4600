#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    switch (fork()) {
        case -1:
            perror("Failed to fork");
            return 1;
        case 0:
            printf("I am child %ld\n", (long) getpid());
            break;
        default:
            printf("I am the parent %ld\n", (long) getpid());
            break;
    }
    return 0;
}