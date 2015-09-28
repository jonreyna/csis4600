/* Program 3.7:
 * The runback program creates a child process to
 * execute a command string in the background.
 */
#include <stdio.h>
#include <unistd.h>

#include "../restart/restart.h"
#include "../makeargv/makeargv.h"

int main(int argc, char *argv[]) {
    /* Used to store the child's PID */
    pid_t childpid;
    /* The delimiters to use with makeargv() */
    char delim[] = " \t";
    /* The double pointer to pass for tokenization to makeargv() */
    char **myargv;

    /* Make sure the argument count is two */
    if (argc != 2) {
        /* If the arg count is not two, print an error */
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        /* return nonzero value to shell to indicate the error condition */
        return 1;
    }
    /* create a clone of this process, and store the returned PID */
    childpid = fork();
    /* If the returned PID is -1, there was a fork() error */
    if (childpid == -1) {
        /* Print an error message */
        perror("Failed to fork");
        /* return nonzero value to shell to indicate the error condition */
        return 1;
    }
    /* If childpid is 0, this is the child's code section */
    if (childpid == 0) {
        /* Attempt to become a new session leader */
        if (setsid() == -1) {
            /* Could not become a new session leader, so print an error message */
            perror("Child failed to become a session leader");
        }
            /* The child process became the leader of a new session.
             * Tokenize the arguments passed into the parent.
             */
        else if (makeargv(argv[1], delim, &myargv) == -1) {
            /* There was an error tokenizing the arguments.
             * Print an error message indicating the error condition
             */
            fprintf(stderr, "Child failed to construct argument array\n");
        }
            /* The child process is the leader of a new session,
             * and its arguments were tokenized successfully.
             * Attempt to execute the first token, and pass the array to the argument list. */
        else {
            execvp(myargv[0], myargv); // the & and [0] are extraneous (passing reference to first element
            perror("Child failed to exec command");
        }
        return 1; /* child should never return */
    }
    return 0; /* parent exits */
}