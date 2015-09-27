#ifndef MAKEARGV_H
#define MAKEARGV_H

#ifdef __cplusplus
extern "C" {
#endif

/* Tokenizes strings given argument s, using the given delimiters,
 * and stores the results in argvp.
 * If there is an error, -1 is returned, otherwise, the number of tokens
 * is returned.
 */
int makeargv(const char *s, const char *delimiters, char ***argvp);

#ifdef __cplusplus
}
#endif

#endif