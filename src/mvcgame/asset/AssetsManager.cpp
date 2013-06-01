
#include <mvcgame/asset/AssetsManager.hpp>


namespace mvcgame {

    AssetsManager::AssetsManager() :
    _textures(*this), _textureAtlases(*this)
    {
    }

    AssetsManager::~AssetsManager()
    {
    }

    template<>
    void AssetsManager::addLoader(std::unique_ptr<IAssetLoader<Texture>> loader)
    {
        return _textures.add(std::move(loader));
    }

    template<>
    void AssetsManager::addLoader(std::unique_ptr<IAssetLoader<TextureAtlas>> loader)
    {
        return _textureAtlases.add(std::move(loader));
    }

    template<>
    std::unique_ptr<Texture> AssetsManager::load(const std::string& name)
    {
        return _textures.load(name);
    }

    template<>
    std::unique_ptr<TextureAtlas> AssetsManager::load(const std::string& name)
    {
        return _textureAtlases.load(name);
    }
}