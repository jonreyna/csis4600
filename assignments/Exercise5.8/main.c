#define _BSD_SOURCE

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

/**
 * Cases
 * 1. It's just a file. Print its path and return.
 * 2. It's a directory. Call yourself with the directory path.
 */
void depthfirst(const char *path) {

    DIR *dirp = NULL;

    if (path == NULL || strncmp(path, "", 1) == 0) {
        return;
    } else if ((dirp = opendir(path)) == NULL) {
        return;
    }

    char *files[128];

    char *nodeArr[128];
    memset(nodeArr, 0, 128);

    int regular_file_count = 0;
    char abs_path[PATH_MAX];
    struct dirent *dentp = NULL;
    while (dentp = readdir(dirp)) {

        if (strcmp(dentp->d_name, ".") == 0 || strcmp(dentp->d_name, "..") == 0)
            continue;

        sprintf(abs_path, "%s/%s", path, dentp->d_name);

        // Check if its a directory
        if (dentp->d_type == DT_DIR) {
            // visit node
            printf("%s\n", abs_path);
            depthfirst(abs_path);
        } else {
            files[regular_file_count] = (char*) malloc(strlen(abs_path) * sizeof(char*));
            strcpy(files[regular_file_count++], abs_path);
        }
    }
    for (--regular_file_count; regular_file_count >= 0; regular_file_count--) {
        printf("%s\n", files[regular_file_count]);
        free(files[regular_file_count]);
    }
    closedir(dirp);
}

int main(int argc, char *argv[]) {
    //    listFiles(argv[1]);
    depthfirst(".");
}