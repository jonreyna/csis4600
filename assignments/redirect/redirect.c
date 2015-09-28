/* Program 4.18:
 * A program that redirects standard output to the
 * file my.file.
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../restart/restart.h"

/* Define the flags to use when opening my.file
 *
 * O_WRONLY: Open for writing only
 * O_CREAT: Create file if it doesn't already exist
 * O_APPEND: Writes are always appended to end of file
 */
#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_APPEND)

/* Define the bit mask that specifies the access mode
 * my.file should be created with.
 *
 * S_IRUSR: 0400 - User-read
 * S_IWUSR: 0200 - User-write
 * S_IRGRP: 040 - Group-read
 * S_IROTH: 04 - Other-read
 */
#define CREATE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main() {
    /* my.file's file descriptor */
    int fd;

    /* Open or create my.file */
    fd = open("my.file", CREATE_FLAGS, CREATE_MODE);
    /* If there was an error opening my.file */
    if (fd == -1) {
        /* Print an error */
        perror("Failed to open my.file");
        /* Return 1 to indicate the error to the shell */
        return 1;
    }
    /* Make a duplicate of my.file's file descriptor using STDOUT_FILENO
     * (if STDOUT_FILENO is open, close it first).
     */
    if (dup2(fd, STDOUT_FILENO) == -1) {
        /* If dup2 returns -1, print an error message */
        perror("Failed to redirect standard output");
        /* And return 1 to the shell to indicate an error occurred */
        return 1;
    }
    /* Close the old file descriptor. */
    if (r_close(fd) == -1) {
        /* If r_close() returned an error, print an error message */
        perror("Failed to close the file");
        /* Return 1 to the shell to indicate the error condition */
        return 1;
    }
    /* Write "OK" to STDOUT_FILENO (my.file) */
    if (write(STDOUT_FILENO, "OK", 2) == -1) {
        /* If an write() returns an error, print an error message */
        perror("Failed in writing to file");
        /* Return 1 to the shell to indicate the error condition */
        return 1;
    }
    /* If we made it here, everything went well. So return 0
     * to the shell to indicate success. */
    return 0;
}