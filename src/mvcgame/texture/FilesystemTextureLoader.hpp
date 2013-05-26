
#ifndef mvcgame_FilesystemTextureLoader_hpp
#define mvcgame_FilesystemTextureLoader_hpp

#include <mvcgame/texture/ITextureLoader.hpp>
#include <memory>
#include <map>
#include <vector>

namespace mvcgame {

    class IFilesystemBridge;

    class FilesystemTextureLoader
    {
    private:
        typedef std::vector<std::unique_ptr<ITextureLoader>> LoaderList;
        typedef std::map<std::string, LoaderList> LoaderMap;
        IFilesystemBridge& _bridge;
        LoaderMap _loaders;

        std::unique_ptr<Texture> load(std::ifstream& in, LoaderList& loaders);
    public:
        FilesystemTextureLoader(IFilesystemBridge& bridge);

        void registerLoader(std::unique_ptr<ITextureLoader> loader, const std::string& ext="");
        std::unique_ptr<Texture> load(const std::string& path);
    };

}

#endif