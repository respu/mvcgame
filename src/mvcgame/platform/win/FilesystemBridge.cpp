

#include <mvcgame/platform/win/FilesystemBridge.hpp>

#ifdef MVCGAME_DEBUG_FILESYSTEM
#include <iostream>
#endif

namespace mvcgame {

    FilesystemBridge::FilesystemBridge()
    {

    }

    bool FilesystemBridge::readResource(const std::string& path, std::ifstream& in)
    {
        return false;
    }

    void FilesystemBridge::setBasePath(const std::string& path)
    {
        _basePath = path;
    }
}