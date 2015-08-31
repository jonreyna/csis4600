#ifndef MAKEARGV_H
#define MAKEARGV_H

#ifdef __cplusplus
extern "C" {
#endif

int makeargv(const char *s, const char *delimiters, char ***argvp);

#ifdef __cplusplus
}
#endif

#endif