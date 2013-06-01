
#include <mvcgame/asset/BaseAssetsManager.hpp>

namespace mvcgame {

    BaseAssetsManager::BaseAssetsManager()
    {
    }

    BaseAssetsManager::~BaseAssetsManager()
    {
    }

    void BaseAssetsManager::addStreamLoader(std::unique_ptr<Loader> loader)
    {      
        _loaders.push_back(std::move(loader));
    }

    bool BaseAssetsManager::loadStream(const std::string& name, Callback callback)
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