#define _BSD_SOURCE
#include <dirent.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/limits.h>
#include "file_perms.h"

static void displayStatInfo(const struct stat *sb)
{
    printf("File type:                   ");

    switch (sb->st_mode &S_IFMT) {
        case S_IFREG: printf("regular file\n"); break;
        case S_IFDIR: printf("directory\n"); break;
        case S_IFCHR: printf("character device\n"); break;
        case S_IFBLK: printf("block device\n"); break;
        case S_IFLNK: printf("symbolic (soft) link\n"); break;
        case S_IFIFO: printf("FIFO or pipe\n"); break;
        case S_IFSOCK: printf("socket\n"); break;
        default: printf("unknown file type?\n");
    }

    printf("device containing i-node: major=%ld   minor=%ld\n", (long) major(sb->st_dev), (long) minor(sb->st_dev));
    printf("I-node number:                  %ld\n", (long) sb->st_ino);
    printf("Mode:                           %lo (%s)\n", (unsigned long) sb->st_mode, filePermStr(sb->st_mode, 0));

    if (sb->st_mode & (S_ISUID | S_ISGID | S_ISVTX))
        printf("    special bits set:    %s%s%s\n",
                (sb->st_mode & S_ISUID) ? "set-UID " : "",
                (sb->st_mode & S_ISGID) ? "set-GID " : "",
                (sb->st_mode & S_ISVTX) ? "sticky" : "");

    printf("Number of (hard) links:    %ld\n", (long) sb->st_nlink);

    printf("Ownership:                 UID=%ld    GID=%ld\n", (long) sb->st_uid, (long) sb->st_gid);

    if (S_ISCHR(sb->st_mode) || S_ISBLK(sb->st_mode))
        printf("Device number (st_rdev): major=%ld minor=%ld\n", (long) major(sb->st_rdev), (long) minor(sb->st_rdev));

    printf("File size:                %lld bytes\n", (long long) sb->st_size);
    printf("Optimal I/O block size:   %ld bytes\n", (long) sb->st_blksize);
    printf("512B blocks allocated:    %lld\n", (long long) sb->st_blocks);
    printf("Last file access:         %s", ctime(&sb->st_atime));
    printf("Last file modification:   %s", ctime(&sb->st_mtime));
    printf("Last status change:       %s", ctime(&sb->st_ctime));
}

static void /* List all directories in 'dirpath' */
listFiles(const char *dirpath)
{
    bool isCurrent; /* true if 'dirpath' is "." */

    isCurrent = strcmp(dirpath, ".") == 0;

    DIR *dirp = NULL;
    dirp = opendir(dirpath);
    if (dirp == NULL) {
        char messageBuf[128];
        sprintf(messageBuf, "opendir failed on '%s'", dirpath);
        perror(messageBuf);
        return;
    }

    /* For each entry in this directory, print directory + filename */

    for (;;) {
        errno = 0;

        struct dirent *dp = NULL;
        dp = readdir(dirp);
        if (dp == NULL)
            break;

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        if (!isCurrent)
            printf("%s/", dirpath);
        printf("%s\n", dp->d_name);
        printf("dp->d_name: %s\n", dp->d_name);

        char absolute_path_buf[PATH_MAX];
        memset(absolute_path_buf, 0, PATH_MAX);
        sprintf(absolute_path_buf, "%s/%s", dirpath, dp->d_name);
        printf("absolute_path_buf: %s", absolute_path_buf);

        struct stat s;
        if (stat(absolute_path_buf, &s) == -1) {
            perror("stat error");
        } else {
            printf("\n");
             displayStatInfo(&s);
        }
    }

    if (errno != 0)
        perror("readdir");

    if (closedir(dirp) == -1)
        perror("closedir");
}

int main(int argc, char *argv[]) {
    listFiles(argv[1]);
}
