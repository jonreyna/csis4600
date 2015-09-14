#include <errno.h>
#include <stdlib.h>
#include <string.h>

/* Tokenizes strings given argument s, using the given delimiters,
 * and stores the results in argvp.
 * If there is an error, -1 is returned, otherwise, the number of tokens
 * is returned.
 */
int makeargv(const char *s, const char *delimiters, char ***argvp) {
    int error;
    int i;
    int numtokens;
    const char *snew;
    char *t;

    /* Ensure that s, delimiters, and argvp are not NULL */
    if ((s == NULL) || (delimiters == NULL) || (argvp == NULL)) {
        /* If they are, set errno to indicate the error */
        errno = EINVAL;
        /* and return -1 to report the error condition back to the
         * caller */
        return -1;
    }
    /* Dereferencing the triple pointer argvp, we get the value
     * of the double pointer passed in, and set it to NULL.
     * I don't see why this is necessary, since we are allocating
     * it new memory with malloc() later.
     */
    *argvp = NULL;

    /* Here we increment the pointer s, by the number of bytes needed to
     * reach the first character not in the delimiter set. */
    snew = s + strspn(s, delimiters); /* snew is real start of string */
    /* Then we allocate, in t, enough bytes to hold snew and a null character. */
    if ((t = malloc(strlen(snew) + 1)) == NULL) {
        /* Problem allocating memory, so let the caller know */
        return -1;
    }
    /* Once allocated, we can copy snew to t */
    strcpy(t, snew);
    /* Initialize automatic variable numtokens */
    numtokens = 0;
    /* Check if there is at least one token. */
    if (strtok(t, delimiters) != NULL) { /* count the number of tokens in s */
        /* Loop through until there are no more tokens, counting each one. */
        for (numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++);
    }

    /* create argument array for ptrs to the tokens */
    if ((*argvp = malloc((numtokens + 1) * sizeof(char *))) == NULL) {
        /* Save errno, in case it is set by free() */
        error = errno;
        free(t);
        errno = error;
        return -1;
    }

    /* insert pointers to tokens into the argument array */
    if (numtokens == 0) {
        /* There were no tokens, so free t. */
        free(t);
    } else {
        /* Reset t to original snew value, since strtok() modified it. */
        strcpy(t, snew);
        /* Put the first token in it's place in the array. */
        **argvp = strtok(t, delimiters);
        for (i = 1; i < numtokens; i++) {
            /* Put a token into each char* in argvp*
             * incrementing the pointer each time to
             * point to the next location in memory with i. */
            *((*argvp) + i) = strtok(NULL, delimiters);
        }
    }
    /* Put in final NULL pointer to mark the end of the array. */
    *((*argvp) + numtokens) = NULL;
    return numtokens;
}
