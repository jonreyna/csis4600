#include <stdio.h>
#include <stdlib.h>

#include "keeploglib.h"
#include "listlib.h"

/*
 * Execute cmd, and store cmd and time
 * in the history list.
 */
int runproc(char *cmd) {

    /* Declare a list element type on the stack
     * to store data from this command execution.
     */
    data_t execute;

    /* Pass a reference to the time_t type,
     * to time(), to set the Epoch time.
     */
    if (time(&(execute.time)) == -1) {
        /* Return -1 to indicate an error condition */
        return -1;
    }

    /* Set the command string to the char* passed. */
    execute.string = cmd;

    /* Requested command could not be executed. */
    if (system(cmd) == -1) {
        /* Return -1 to indicate an error condition */
        return -1;
    }

    /* Add the newly created node to our list. */
    /* Everything went okay, so add the newly created
     * node to our list.
     */
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

