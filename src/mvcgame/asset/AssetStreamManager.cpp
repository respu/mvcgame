
#include <mvcgame/asset/AssetStreamManager.hpp>

namespace mvcgame {

    AssetStreamManager::AssetStreamManager()
    {
    }

    void AssetStreamManager::addLoader(std::unique_ptr<Loader> loader)
    {      
        _loaders.push_back(std::move(loader));
    }

    bool AssetStreamManager::load(const std::string& name, Callback callback)
    {
        for(std::unique_ptr<Loader>& loader : _loaders)
        {
            if(loader->load(name, callback))
            {
                return true;
            }
        }
        return false;
    }
}