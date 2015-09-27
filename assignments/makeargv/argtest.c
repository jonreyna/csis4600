#include <stdio.h>

#include "makeargv.h"

int main(int argc, char *argv[]) {
    /* Define the tokens to use as delimiters. */
    char delim[] = " \t";
    char **myargv;
    int numtokens;

    /* Make sure we have only two arguments (program name and a string). */
    if (argc != 2) {
        /* If we don't, print the usage as an error */
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        /* Return 1 (non-zero) to tell the shell to indicate
         * we terminated with an error. */
        return 1;
    }

    /* Use makeargv() to tokenize the argument(s) and store them
     * as tokens in the char** myargv */
    if ((numtokens = makeargv(argv[1], delim, &myargv)) == -1) {
        fprintf(stderr, "Failed to construct an argument array for %s\n", argv[1]);
        return 1;
    }
    printf("The argumetn array contains:\n");
    /* Print each token in myargv */
    for (int i = 0; i < numtokens; i++)
        printf("%d:%s\n", i, myargv[i]);

    /* Note that we never freed the memory allocated by makeargv.
     * If this was a long running program, we would have issues
     * due to a memory leak allocated in t. */
    return 0;
}


