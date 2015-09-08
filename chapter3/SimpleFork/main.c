#include <unistd.h>
#include <stdio.h>

int main() {
    int x = 0;
    fork();
    x = 1;
    printf("I am process %ld and my x is %d\n", (long) getpid(), x);
    return 0;
}