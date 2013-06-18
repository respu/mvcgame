
#include <mvcgame/asset/AssetsManager.hpp>

namespace mvcgame {

    AssetsManager::AssetsManager() :
    _textures(*this),
    _textureAtlases(*this),
    _fontAtlases(*this),
    _tileMaps(*this)
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
    void AssetsManager::addLoader(std::unique_ptr<IAssetLoader<TileMap>> loader, const std::string& tag)
    {
        return _tileMaps.add(std::move(loader), tag);
    }    

    template<>
    std::shared_ptr<Texture> AssetsManager::load(const std::string& name)
    {
        return _textures.load(name);
    }

    template<>
    std::shared_ptr<TextureAtlas> AssetsManager::load(const std::string& name)
    {
        return _textureAtlases.load(name);
    }

    template<>
    std::shared_ptr<FontAtlas> AssetsManager::load(const std::string& name)
    {
        return _fontAtlases.load(name);
    }

    template<>
    std::shared_ptr<TileMap> AssetsManager::load(const std::string& name)
    {
        return _tileMaps.load(name);
    }    

    SpriteSheet AssetsManager::loadSheet(const TextureAtlas& atlas)
    {
        std::shared_ptr<Texture> texture = load<Texture>(atlas.getTextureName());
        return SpriteSheet(texture, atlas);
    }

    FontSheet AssetsManager::loadSheet(const FontAtlas& atlas)
    {
        FontSheet sheet;
        sheet.setInfo(atlas.getInfo());
        for(const FontAtlas::Page& page : atlas.getPages())
        {
            std::shared_ptr<Texture> texture = load<Texture>(page.getTextureName());
            for(const FontAtlas::Page::Region& region : page.getRegions())
            {
                sheet.setLetter(region.name, FontLetter(texture, region));
            }
        }
        return sheet;
    }
}