#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keeploglib.h"

#ifndef MAX_CANNON
/* MAX_CANON is not defined, so define it */
#define MAX_CANON 8192
#endif

int main(int argc, char *argv[]) {
    /* Allocate enough space on the stack
     * for a long command
     */
    char cmd[MAX_CANON];
    int history = 1;

    /* The command was executed without arguments */
    if (argc == 1) {
        history = 0;
    }
    else if ((argc > 2) || strcmp(argv[1], "history")) {
        /* Either too many arguments given, or the
         * command was not executed with "history"
         * as the first parameter.
         *
         * Print a usage message to stderr, and exit with
         * return value 1.
         */
        fprintf(stderr, "Usage: %s [history]\n", argv[0]);
        return 1;
    }

    /* Read from stdin until we get to EOF, '\n', or
     * MAX_CANON - 1, and store what was read into
     * cmd.
     *
     * If fgets() fails, it will return NULL, and so
     * its return value is properly checked here.
     */
    while (fgets(cmd, MAX_CANON, stdin) != NULL) {
        /* We are not assuming that a new line character
         * is read to avoid input truncation.
         *
         * If a newline character was read, then NULL
         * terminate the string by overwriting '\n' with 0.
         */
        if (*(cmd + strlen(cmd) - 1) == '\n') {
            *(cmd + strlen(cmd) - 1) = 0;
        }

        /*
         * If the history command was read, and the history
         * flag was set as an argument, the print the history
         * to stdout.
         */
        if (history && !strcmp(cmd, "history")) {
            showhistory(stdout);
        }
            /* Otherwise, run the command.
             *
             * There's a bug here. An error won't be detected
             * if runproc() does not return 0. This can happen
             * if, for example, time() returns -1.
             */
        else if (runproc(cmd)) {
            perror("Failed to execute command");
            break;
        }
    }

    /* We're done executing user commands.
     * Show the command history and exit with
     * return value 0.
     */
    printf("\n\n>>>>>The list of commands executed is:\n");
    showhistory(stdout);
    return 0;
}
