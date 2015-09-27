/*
 * Program 3.6: execcmdargv.c
 * A program that creates a child process to execute a command
 * string passed as the first command-line argument.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../restart/restart.h"
#include "../makeargv/makeargv.h"

/* makeargv() prototype was omitted since it is defined in the included header. */


int main(int argc, char *argv[]) {
    /* The child's PID */
    pid_t childpid;
    /* The delimiers passed to makeargv() */
    char delim[] = " \t";
    /* The double pointer used as an argument to makeargv() */
    char **myargv;

    /* Make sure the argument count is 2 */
    if (argc != 2) {
        /* Print a usage message to stderr if we don't have two arguments */
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        /* Let the shell know about the error condition with a nonzero return value */
        return 1;
    }
    /* Clone this process to create the child process,
     * and store its PID in childpid */
    childpid = fork();
    /* Check if fork() executed successfully */
    if (childpid == -1) {
        /* If it did not, print an error message */
        perror("Failed to fork");
        /* Let the shell know about the error condition with a nonzero return value */
        return 1;
    }

    /* If childpid is 0, then we are in the child process */
    if (childpid == 0) {
        /* Execute makeargv() and check its return value for error conditions */
        if (makeargv(argv[1], delim, &myargv) == -1) {
            /* makeargv() encountered an error, print an error message */
            perror("Child failed to construct argument array");
        } else {
            /* Execute the requested process with its arguments (tokenized by makeargv()) */
            execvp(myargv[0], &myargv[0]);
            /* execvp() returned, so an error occurred */
            perror("Child failed to exec command");
        }
        /* Let the shell know about the error condition with a nonzero return value */
        return 1;
    }
    /* Wait for the child to terminate, discarding its return status */
    /* If the childpid is returned by wait(), it was successful */
    if (childpid != r_wait(NULL)) { /* parent code */
        /* Print a message indicating the error condition */
        perror("Parent failed to wait");
        /* Let the shell know about the error condition with a nonzero return value */
        return 1;
    }
    /* Everything executed correctly, so let the shell know with a zero return status */
    return 0;
}