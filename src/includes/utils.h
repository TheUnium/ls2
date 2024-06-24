#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <filesystem>

#define COLOR_RESET "\x1B[0m"
#define COLOR_FILE "\x1B[0;36m"
#define COLOR_DIR "\x1B[0;34m"
#define COLOR_YELLOW "\x1B[33m"

std::string getColor(const std::filesystem::file_status &status);
std::string getFilePermissions(const std::filesystem::file_status &status, bool numeric);

#endif