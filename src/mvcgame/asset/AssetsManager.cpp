

#include <mvcgame/asset/AssetsManager.hpp>
#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/base/Application.hpp>

namespace mvcgame {

    AssetsManager::AssetsManager(Application& app) :
    _app(app)
    {

    }

    void AssetsManager::registerLoader(std::unique_ptr<IAssetLoader> loader)
    {
        _assetLoaders.push_back(std::move(loader));
    }

    void AssetsManager::registerLoader(std::unique_ptr<ITextureLoader> loader)
    {
        _textureLoaders.push_back(std::move(loader));
    }

    bool AssetsManager::loadTextureStream(std::istream& in, std::unique_ptr<Texture>* texture)
    {
        for(std::unique_ptr<ITextureLoader>& textureLoader : _textureLoaders)
        {
            in.seekg(0, std::ios::beg);
            if(textureLoader->validate(in))
            {
                in.seekg(0, std::ios::beg);
                *texture = textureLoader->load(in);
                if(*texture)
                {
                    return true;
                }
            }
        }
        return false;
    }

    std::unique_ptr<Texture> AssetsManager::loadTexture(const std::string& name)
    {
        std::unique_ptr<Texture> texture;
        IAssetLoader::Callback callback = std::bind(&AssetsManager::loadTextureStream, this, std::placeholders::_1, &texture);
        for(std::unique_ptr<IAssetLoader>& assetLoader : _assetLoaders)
        {
            if(assetLoader->load(name, callback))
            {
                break;
            }
        }
        return std::move(texture);
    }

}