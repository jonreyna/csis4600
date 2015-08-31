#include <stdio.h>
#include <stdlib.h>

#include "keeploglib.h"
#include "listlib.h"

/* execute cmd; store cmd and time in history list */
int runproc(char *cmd) {
    data_t execute;

    if (time(&(execute.time)) == -1)
        return -1;
    execute.string = cmd;
    /* command could not be executed at all */
    if (system(cmd) == -1)
        return -1;
    return adddata(execute);
}

/* output the history list of the file f */
void showhistory(FILE *f) {
    data_t data;
    int key;

    key = accessdata();
    if (key == -1) {
        fprintf(f, "No history\n");
        return;
    }
    while (!getdata(key, &data) && (data.string != NULL)) {
        fprintf(f, "Command: %s\nTime: %s\n", data.string, ctime(&(data.time)));
        free(data.string);
    }
}

