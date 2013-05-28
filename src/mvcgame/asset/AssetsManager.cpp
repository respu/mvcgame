

#include <mvcgame/asset/AssetsManager.hpp>
#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/base/Application.hpp>

namespace mvcgame {

    AssetsManager::AssetsManager(Application& app) :
    _app(app)
    {

    }

    void AssetsManager::registerLoader(std::unique_ptr<INameTextureLoader> loader)
    {
        _textureLoaders.push_back(std::move(loader));
    }

    std::unique_ptr<Texture> AssetsManager::loadTexture(const std::string& name)
    {
        for(std::unique_ptr<INameTextureLoader>& loader : _textureLoaders)
        {
            if(loader->validate(name))
            {
                return loader->load(name);
            }
        }
        return std::unique_ptr<Texture>();
    }

}