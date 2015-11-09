//
// Created by meddling_monk on 11/8/15.
//

#ifndef FLEXIBLERING_H
#define FLEXIBLERING_H

#include <string>
#include <map>
#include <dirent.h>

// A Node in the Flexible ring
class Node {
private:
    // The path name of the fifo
    std::string pathname;
public:
    Node(std::string pathname);
};

class FlexibleRing {

private:
    std::map<std::string, ino_t> nodes;
public:
    int ReadCurrentNodes(std::string pathname);

    void PrintNodes();

    void AddNode(std::string pathname, mode_t mode);

    void RmNode(std::string pathname);
};


#endif //FLEXIBLERING_H
