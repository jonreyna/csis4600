#define _BSD_SOURCE

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

/**
 * Cases
 * 1. It's a file. Place it on the stack to be called after full depth has been reached.
 * 2. It's a directory (recursive case). Call self with the directory path.
 */
void depthfirst(const char *path) {

    DIR *dirp = NULL;


    /* Check if this is the end of the path.
     * If it is, just return.
     * Otherwise, open the directory.
     */
    if (path == NULL || strncmp(path, "", 1) == 0) {
        return;
    } else if ((dirp = opendir(path)) == NULL) {
        return;
    }

    // Holds the regular file names in this directory.
    char *regular_file_names[128];
    // Keep a count of regular files in this directory.
    int regular_file_count = 0;
    // The current d_name.
    char abs_path[256];
    // Directory entry pointer to keep handle to the current element in the stream.
    struct dirent *dentp = NULL;
    while (dentp = readdir(dirp)) {

        // If the path is the current or parent directory, skip this iteration.
        if (strcmp(dentp->d_name, ".") == 0 || strcmp(dentp->d_name, "..") == 0) {
            continue;
        }

        // Store the full path with the file name.
        sprintf(abs_path, "%s/%s", path, dentp->d_name);

        // Check if this entry is a directory.
        if (dentp->d_type == DT_DIR) {
            // If it is, visit the node.
            printf("%s\n", abs_path);
            // This is the recursive case, so call self with the path.
            depthfirst(abs_path);
        } else {
            // This is not a directory. Allocate space on the array/stack, and store
            // the file name to print later.
            regular_file_names[regular_file_count] = (char *) malloc(strlen(abs_path) * sizeof(char *));
            strcpy(regular_file_names[regular_file_count++], abs_path);
        }
    }
    // Print files from the array/stack in FILO order.
    for (--regular_file_count; regular_file_count >= 0; --regular_file_count) {
        printf("%s\n", regular_file_names[regular_file_count]);
        // Free the mallocs!
        free(regular_file_names[regular_file_count]);
    }
    // Close this directory stream.
    closedir(dirp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s %s\n", argv[0], "[example directory path]");
    } else {
        depthfirst(argv[1]);
    }
}