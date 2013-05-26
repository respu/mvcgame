

#ifndef mvcgame_IFilesystemBridge_hpp
#define mvcgame_IFilesystemBridge_hpp

#include <string>
#include <fstream>

namespace mvcgame {

    class IFilesystemBridge
    {
    public:
        virtual ~IFilesystemBridge(){};

        virtual bool readResource(const std::string& path, std::ifstream& in) = 0;
    };

}

#endif