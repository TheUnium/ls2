#include "includes/ls2.h"
#include "includes/utils.h"
#include "includes/fileinfo.h"

#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

void listDirectory(const std::string &path, bool showHidden, bool numericPermissions) {
    // error thrown if the path specified doesnt exist. (ls2 [path to dir thats non-existent])
    if (!fs::exists(path)) {
        throw std::runtime_error("Directory doesn't exist. Is the inputted path correct?");
    }

    // error thrown if the path specified isnt a dir. (ls2 [path to a file])
    if (!fs::is_directory(path)) {
        throw std::runtime_error("Path is a file.");
    }

    std::vector<FileInfo> entries;
    for (const auto &entry : fs::directory_iterator(path)) {
        if (!showHidden && entry.path().filename().string().at(0) == '.') {
            continue;
        }
        entries.push_back(FileInfo(entry.path()));
    }

    std::sort(entries.begin(), entries.end(), [](const FileInfo &a, const FileInfo &b) {
        if (fs::is_directory(a.getPath()) && !fs::is_directory(b.getPath())) {
            return true;
        } else if (!fs::is_directory(a.getPath()) && fs::is_directory(b.getPath())) {
            return false;
        } else {
            return a.getName() < b.getName();
        }
    });

    int maxNameWidth = 0;
    for (const auto &entry : entries) {
        if (entry.getName().length() > maxNameWidth) {
            maxNameWidth = entry.getName().length();
        }
    }
    maxNameWidth += 2;

    // column names, bold and underlined
    std::cout << std::left << std::setw(maxNameWidth) << "\033[1m\033[4mName\033[0m" << "  "
              << std::right << std::setw(32) << "\033[1m\033[4mSize\033[0m" << "  "
              << std::right << std::setw(9) << "\033[1m\033[4mPermissions\033[0m" << "  "
              << "\033[1m\033[4mLast Modified\033[0m" << "\n";

    for (const auto &entry : entries) {
        std::cout << entry.format(maxNameWidth, numericPermissions) << "\n";
    }
}
