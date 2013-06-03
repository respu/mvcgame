
#include <mvcgame/asset/AssetsManager.hpp>

namespace mvcgame {

    AssetsManager::AssetsManager() :
    _textures(*this),
    _textureAtlases(*this),
    _fontAtlases(*this)
    {
    }

    AssetsManager::~AssetsManager()
    {
    }

    template<>
    void AssetsManager::addLoader(std::unique_ptr<IAssetLoader<Texture>> loader, const std::string& tag)
    {
        return _textures.add(std::move(loader), tag);
    }

    template<>
    void AssetsManager::addLoader(std::unique_ptr<IAssetLoader<TextureAtlas>> loader, const std::string& tag)
    {
        return _textureAtlases.add(std::move(loader), tag);
    }

    template<>
    void AssetsManager::addLoader(std::unique_ptr<IAssetLoader<FontAtlas>> loader, const std::string& tag)
    {
        return _fontAtlases.add(std::move(loader), tag);
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

    template<>
    std::unique_ptr<FontAtlas> AssetsManager::load(const std::string& name)
    {
        return _fontAtlases.load(name);
    }    
}