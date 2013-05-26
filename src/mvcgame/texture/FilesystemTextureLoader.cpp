
#include <mvcgame/texture/FilesystemTextureLoader.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/platform/IFilesystemBridge.hpp>

namespace mvcgame {

    FilesystemTextureLoader::FilesystemTextureLoader(IFilesystemBridge& bridge) :
    _bridge(bridge)
    {
    }

    void FilesystemTextureLoader::registerLoader(std::unique_ptr<ITextureLoader> loader, const std::string& ext)
    {
        LoaderList& list = _loaders[ext];
        list.push_back(std::move(loader));
    }

    std::unique_ptr<Texture> FilesystemTextureLoader::load(std::ifstream& in, LoaderList& loaders)
    {
        for(std::unique_ptr<ITextureLoader>& loader : loaders)
        {
            in.seekg(0, std::ios::beg);
            if(loader->validate(in))
            {
                in.seekg(0, std::ios::beg);
                return loader->load(in);
            }
        }
        return std::unique_ptr<Texture>();
    }

    std::unique_ptr<Texture> FilesystemTextureLoader::load(const std::string& path)
    {
        std::ifstream in;
        if(!_bridge.readResource(path, in))
        {
            return std::unique_ptr<Texture>();
        }
        std::string ext = path.substr(path.find_last_of('.')+1);
        LoaderMap::iterator itr = _loaders.find(ext);
        if(itr != _loaders.end())
        {
            std::unique_ptr<Texture> t = std::move(load(in, itr->second));
            if(t)
            {
                return std::move(t);
            }
        }
        itr = _loaders.find("");
        if(itr != _loaders.end())
        {
            return std::move(load(in, itr->second));
        }
        return std::unique_ptr<Texture>();
    }

}