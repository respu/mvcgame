
#ifndef mvcgame_FilesystemTextureLoader_hpp
#define mvcgame_FilesystemTextureLoader_hpp

#include <mvcgame/texture/IStreamTextureLoader.hpp>
#include <mvcgame/texture/INameTextureLoader.hpp>

#include <memory>
#include <map>
#include <vector>

namespace mvcgame {

    class IFilesystemBridge;

    class FilesystemTextureLoader : public INameTextureLoader
    {
    public:
        typedef IStreamTextureLoader IChildLoader;
    private:
        typedef std::vector<std::string> Paths;        
        typedef std::vector<std::unique_ptr<IChildLoader>> LoaderList;
        typedef std::map<std::string, LoaderList> LoaderMap;

        Paths _paths;
        IFilesystemBridge& _bridge;
        LoaderMap _loaders;

        std::unique_ptr<Texture> loadStream(std::ifstream& in, LoaderList& loaders);
        std::unique_ptr<Texture> loadPath(const std::string& name);
    public:
        FilesystemTextureLoader(IFilesystemBridge& bridge);

        void registerLoader(std::unique_ptr<IChildLoader> loader, const std::string& ext="");
        
        std::unique_ptr<Texture> load(const std::string& name);

        void addPath(const std::string& path);
    };

}

#endif