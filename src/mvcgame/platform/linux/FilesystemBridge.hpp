

#ifndef mvcgame_linux_FilesystemBridge_hpp
#define mvcgame_linux_FilesystemBridge_hpp

#include <mvcgame/platform/IFilesystemBridge.hpp>

namespace mvcgame {

    class FilesystemBridge : public IFilesystemBridge
    {
    private:
        std::string _basePath;
        std::string _exePath;
    public:

        FilesystemBridge();

        bool readResource(const std::string& path, std::ifstream& in);

        void setBasePath(const std::string& path);
    };

}

#endif