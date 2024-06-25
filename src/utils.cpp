#include "includes/utils.h"

#include <sstream>

// used to color code directories and files
std::string getColor(const std::filesystem::file_status &status) {
    if (std::filesystem::is_directory(status)) {
        return COLOR_DIR; // cyan, see includes/utils.h
    }
    return COLOR_FILE; // teal, see includes/utils.h
}

// returns file perms as string or as numericals ("Permissions" column)
std::string getFilePermissions(const std::filesystem::file_status& status, bool numeric) {
    std::ostringstream ss;
    if (numeric) {
        ss << std::oct << (static_cast<int>(status.permissions()) & static_cast<int>(std::filesystem::perms::mask));
    } else {
        auto perms = status.permissions();
        ss << ((perms & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? 'r' : '-')
           << ((perms & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? 'w' : '-')
           << ((perms & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? 'x' : '-')
           << ((perms & std::filesystem::perms::group_read) != std::filesystem::perms::none ? 'r' : '-')
           << ((perms & std::filesystem::perms::group_write) != std::filesystem::perms::none ? 'w' : '-')
           << ((perms & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? 'x' : '-')
           << ((perms & std::filesystem::perms::others_read) != std::filesystem::perms::none ? 'r' : '-')
           << ((perms & std::filesystem::perms::others_write) != std::filesystem::perms::none ? 'w' : '-')
           << ((perms & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? 'x' : '-');
    }
    return ss.str();
}
