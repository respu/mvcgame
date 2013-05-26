

#include <mvcgame/platform/linux/FilesystemBridge.hpp>
#include <unistd.h>

#define PATH_MAX 1024
#define DIR_SEP '/'

#ifdef MVCGAME_DEBUG_FILESYSTEM
#include <iostream>
#endif

namespace mvcgame {

    FilesystemBridge::FilesystemBridge()
    {
        char dest[PATH_MAX];
        readlink("/proc/self/exe", dest, PATH_MAX);
        _exePath = dest;
        _exePath = _exePath.substr(0, _exePath.find_last_of(DIR_SEP));
    }

    bool FilesystemBridge::readResource(const std::string& path, std::ifstream& in)
    {
        std::string p = path;
        if(p[0] != DIR_SEP)
        {
            p = _basePath + DIR_SEP + p;
        }
        if(p[0] != DIR_SEP)
        {
            p = _exePath + DIR_SEP + p;
        }

#ifdef MVCGAME_DEBUG_FILESYSTEM
        std::cout << ">>>>" << std::endl;        
        std::cout << "FilesystemBridge::readResource" << std::endl;
        std::cout << path << std::endl;
        std::cout << p << std::endl;
        std::cout << "<<<<" << std::endl;
#endif

        in.open(p, std::ios::binary);
        return true;
    }

    void FilesystemBridge::setBasePath(const std::string& path)
    {
        _basePath = path;
    }
}