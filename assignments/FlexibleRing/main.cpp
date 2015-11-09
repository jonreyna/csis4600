#include <iostream>
#include <sys/stat.h>
#include "FlexibleRing.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [directory path]\n";
        return 1;
    }

    FlexibleRing f;

    try {
        f.ReadCurrentNodes(".");
    } catch (std::exception &e) {
        std::cout << e.what();
    }
    f.PrintNodes();
    std::cout << "adding a node\n";
    f.AddNode(argv[1], S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    std::cout << "printing nodes\n";
    f.PrintNodes();
}