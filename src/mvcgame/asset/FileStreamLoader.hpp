
#ifndef mvcgame_FileStreamLoader_hpp
#define mvcgame_FileStreamLoader_hpp

#include <mvcgame/asset/IStreamLoader.hpp>

#include <memory>
#include <vector>

namespace mvcgame {

    class IFilesystemBridge;

    class FileStreamLoader : public IStreamLoader
    {
    private:
        typedef std::vector<std::string> Paths;        

        Paths _paths;
        IFilesystemBridge& _bridge;
    public:

        FileStreamLoader(IFilesystemBridge& bridge);

        /**
         * @see IStreamLoader
         */
        bool validate(const std::string& name);

        /**
         * @see IStreamLoader
         */
        bool load(const std::string& name, Callback callback);

        /**
         * Add a path to search for assets
         */
        void addPath(const std::string& path);
    };

}

#endif