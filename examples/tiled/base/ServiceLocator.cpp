
#include "tiled/base/ServiceLocator.hpp"

#include <mvcgame/texture/PngTextureLoader.hpp>
#include <mvcgame/tile/TmxTileMapLoader.hpp>

using namespace mvcgame;

ServiceLocator& ServiceLocator::get()
{
    static ServiceLocator locator;
    return locator;    
}

ServiceLocator::ServiceLocator()
{
    _textures.setStreamManager(_assetStreams);
    _textureAtlases.setStreamManager(_assetStreams);
    _fontAtlases.setStreamManager(_assetStreams);
    _tileMaps.setStreamManager(_assetStreams);

    _textures.add(std::unique_ptr<PngTextureLoader>(new PngTextureLoader()), "png");

    std::unique_ptr<TmxTileMapLoader> tmx(new TmxTileMapLoader());
    tmx->setStreamManager(_assetStreams);
    tmx->setTextureManager(_textures);
    _tileMaps.add(std::move(tmx), "tmx");
}

AssetStreamManager& ServiceLocator::getAssetStreams()
{
    return _assetStreams;
}

AssetManager<Texture>& ServiceLocator::getTextures()
{
    return _textures;
}

AssetManager<TextureAtlas>& ServiceLocator::getTextureAtlases()
{
    return _textureAtlases;
}

AssetManager<FontAtlas>& ServiceLocator::getFontAtlases()
{
    return _fontAtlases;
}

AssetManager<TileMap>& ServiceLocator::getTileMaps()
{
    return _tileMaps;
}
