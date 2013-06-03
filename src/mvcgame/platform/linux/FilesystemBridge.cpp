

#include <mvcgame/platform/linux/FilesystemBridge.hpp>
#include <unistd.h>
#include <dirent.h>

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

    std::string FilesystemBridge::fixPath(const std::string& path)
    {
        std::string p = path;
        if(p[0] != DIR_SEP)
        {
            p = _exePath + DIR_SEP + p;
        }
        return p;
    }

    bool FilesystemBridge::readResource(const std::string& path, std::ifstream& in)
    {
        std::string p = fixPath(path);

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

    FilesystemBridge::Paths FilesystemBridge::findResource(const std::string& name, const std::string& path)
    {
        DIR *dir;
        struct dirent *ent;
        Paths results;
        std::string p = fixPath(path);

        if((dir = opendir(p.c_str())) != nullptr)
        {
            while((ent = readdir(dir)) != nullptr)
            {
                std::string filename = ent->d_name;
                if(filename.find(name) != std::string::npos)
                {
                    results.push_back(p+DIR_SEP+filename);
                }
            }
            closedir (dir);
        }

#ifdef MVCGAME_DEBUG_FILESYSTEM
        std::cout << ">>>>" << std::endl;        
        std::cout << "FilesystemBridge::findResource" << std::endl;
        std::cout << name << " " << path << std::endl;
        for(const std::string& r : results)
        {
            std::cout << r << std::endl;
        }
        std::cout << "<<<<" << std::endl;
#endif

        return results;
    }
}