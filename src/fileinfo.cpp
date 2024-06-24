#include "includes/fileinfo.h"
#include "includes/utils.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

FileInfo::FileInfo(const std::filesystem::path &path) : path(path), status(std::filesystem::status(path)) {}

std::string FileInfo::getName() const {
    return path.filename().string();
}

const std::filesystem::path& FileInfo::getPath() const {
    return path;
}

std::string FileInfo::format(int maxNameWidth, bool numericPermissions) const {
    std::ostringstream ss;
    auto ftime = std::filesystem::last_write_time(path);
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        ftime - decltype(ftime)::clock::now() + std::chrono::system_clock::now()
    );
    std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
    std::string timeStr = std::asctime(std::localtime(&cftime));
    timeStr.pop_back();

    ss << getColor(status) << std::left << std::setw(maxNameWidth) << getName() << COLOR_RESET;

    if (std::filesystem::is_regular_file(path)) {
        ss << std::right << std::setw(10) << std::filesystem::file_size(path) << "  "; // shows file size
    } else if (std::filesystem::is_directory(path)) {
        ss << std::right << std::setw(10) << "<DIR>" << "  "; // if its a directory, return <DIR> instead of file size
    } else {
        ss << std::right << std::setw(10) << "<UNKNOWN>" << "  ";
    }

    ss << getFilePermissions(status, numericPermissions) << "  "
       << COLOR_YELLOW << timeStr << COLOR_RESET;
    return ss.str();
}
