#include "includes/ls2.h"

#include <iostream>

int main(int argc, char *argv[]) {
    std::string path = ".";
    bool showHidden = false;
    bool numericPermissions = false;
    bool showVersion = false;
    bool showHelp = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-a") {
            showHidden = true;
        } else if (arg == "-n") {
            numericPermissions = true;
        } else if (arg == "-v") {
            showVersion = true;
        } else if (arg == "-h") {
            showHelp = true;
        } else {
            path = arg;
        }
    }

    if (showVersion) {
        std::cout << "ls2 - list files and folders in an organized manner\n"
                  << "running v2.0";
        return 0;
    }

    if (showHelp) {
        std::cout << "Usage:\n  ls2 [options] [path]\n\n"
                  << "Options:\n"
                  << "  -a  Show hidden files\n"
                  << "  -n  Show permissions in numerical form\n"
                  << "  -v  Show version information\n"
                  << "  -h  Show this help message\n";
        return 0;
    }

    try {
        listDirectory(path, showHidden, numericPermissions);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}