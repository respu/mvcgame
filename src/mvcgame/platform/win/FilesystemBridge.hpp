

#ifndef mvcgame_win_FilesystemBridge_hpp
#define mvcgame_win_FilesystemBridge_hpp

#include <mvcgame/platform/IFilesystemBridge.hpp>

namespace mvcgame {

    class FilesystemBridge : public IFilesystemBridge
    {
    private:
        std::string _exePath;
    public:

        FilesystemBridge();

        bool readResource(const std::string& path, std::ifstream& in);

        Paths findResource(const std::string& name, const std::string& path);
    };

}

#endif