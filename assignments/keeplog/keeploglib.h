#ifndef KEEPLOGLIB_H
#define KEEPLOGLIB_H

#ifdef __cplusplus
extern "C" {
#endif

int runproc(char *cmd);

void showhistory(FILE *f);

#ifdef __cplusplus
}
#endif

#endif
