#ifndef FILEINFO_H
#define FILEINFO_H

#include <string>
#include <filesystem>

class FileInfo {
public:
    FileInfo(const std::filesystem::path &path);
    std::string getName() const;
    std::string format(int maxNameWidth, bool numericPermissions) const;
    const std::filesystem::path& getPath() const;

private:
    std::filesystem::path path;
    std::filesystem::file_status status;
};

#endif
