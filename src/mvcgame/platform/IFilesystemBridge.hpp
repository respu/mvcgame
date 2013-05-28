

#ifndef mvcgame_IFilesystemBridge_hpp
#define mvcgame_IFilesystemBridge_hpp

#include <string>
#include <fstream>
#include <vector>

namespace mvcgame {

    class IFilesystemBridge
    {
    public:
        typedef std::vector<std::string> Paths;

        virtual ~IFilesystemBridge(){};

        virtual bool readResource(const std::string& path, std::ifstream& in) = 0;

        virtual Paths findResource(const std::string& name, const std::string& path) = 0;
    };

}

#endif