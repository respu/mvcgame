
#include "hello/base/ServiceLocator.hpp"

#include <mvcgame/texture/PngTextureLoader.hpp>
#include <mvcgame/texture/GdxTextureAtlasLoader.hpp>
#include <mvcgame/font/FntFontAtlasLoader.hpp>

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

    _textures.add(std::unique_ptr<PngTextureLoader>(new PngTextureLoader()), "png");

    std::unique_ptr<GdxTextureAtlasLoader> gdx(new GdxTextureAtlasLoader());
    gdx->setTextureManager(_textures);
    _textureAtlases.add(std::move(gdx), "gdx");

    std::unique_ptr<FntFontAtlasLoader> fnt(new FntFontAtlasLoader());
    fnt->setTextureManager(_textures);
    _fontAtlases.add(std::move(fnt), "fnt");
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
