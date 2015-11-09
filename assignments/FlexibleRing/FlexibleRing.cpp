//
// Created by meddling_monk on 11/8/15.
//

#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <libgen.h>
#include "FlexibleRing.h"

Node::Node(std::string path) {
    pathname = pathname;
}

int FlexibleRing::ReadCurrentNodes(std::string pathname) {
    auto dirp = opendir(pathname.c_str());
    if (dirp == nullptr)
        throw "failed opening the current working directory";

    struct dirent *dp;
    while (dp = readdir(dirp)) {

        if (dp->d_type != DT_FIFO) {
            continue;
        } else if (nodes.find(dp->d_name) != nodes.end()) {
            continue;
        }

        nodes[dp->d_name] = dp->d_ino;
        auto childpid = fork();
        if (childpid == -1) {
            throw strerror(errno);
        } else if (childpid > 0) {
            auto readFd = open(dp->d_name, O_RDONLY);
            if (dup2(readFd, STDOUT_FILENO) == -1) {
                throw strerror(errno);
            } else if (close(readFd) == -1) {
                throw strerror(errno);
            }
        } else {
            auto writeFd = open(dp->d_name, O_WRONLY);
            if (dup2(writeFd, STDIN_FILENO) == -1) {
                throw strerror(errno);
            } else if (close(writeFd) == -1) {
                throw strerror(errno);
            }
        }
        if (childpid) {
            break;
        }
    }

    if (closedir(dirp) == -1)
        throw "failed closing direcotry";
}

void FlexibleRing::PrintNodes() {
    for (auto it : nodes) {
        std::cout << "file: " << it.first << ", inode: " << it.second << std::endl;
    }
}

void FlexibleRing::AddNode(std::string pathname, mode_t mode) {

    if (nodes.count(pathname)) {
        // The key exists in the map, so the fifo already exists.
        return;
    }

    umask(0);
    if (mkfifo(pathname.c_str(), mode) == -1 &&
        errno != EEXIST) {
        throw strerror(errno);
    } else {
        auto path = strdup(pathname.c_str());
        auto newPath = std::string(dirname(path));
        free(path);
        ReadCurrentNodes(newPath);
    }
}

void FlexibleRing::RmNode(std::string pathname) {

}
