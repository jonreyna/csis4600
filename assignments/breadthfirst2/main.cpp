#include <iostream>
#include <dirent.h>
#include <string.h>
#include <vector>


static void listFiles(const char *dirpath)
{
    DIR *dirp;
    struct dirent *dp;
    bool isCurrent;

    isCurrent = strcmp(dirpath, ".") == 0;

    dirp = opendir(dirpath);
    if (dirp == NULL) {
        perror("opendir failed");
        return;
    }

    std::vector<dirent*> dir_vec;
    dir_vec.push_back(readdir(dirp));

    while (!dir_vec.empty()) {
        errno = 0;
        dp = dir_vec.front();
        if (dp == NULL){
            break;
        } else {
            dir_vec.pop_back();
        }

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        while(readdir(dirp))

    }

    if (errno == 0)
        perror("readdir");

    if(closedir(dirp) == -1)
        perror("closedir");

}
int main(int argc, char *argv[]) {

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        printf("%s [dir..]\n", argv[0]);

    if (argc == 1)
        listFiles(".");
    else
        for (argv++; *argv; argv++)
            listFiles(*argv);

    return 0;

}