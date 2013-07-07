
#include "hello/base/ServiceLocator.hpp"

#include <mvcgame/texture/PngTextureLoader.hpp>
#include <mvcgame/texture/GdxTextureAtlasLoader.hpp>
#include <mvcgame/texture/CocosTextureAtlasLoader.hpp>
#include <mvcgame/font/FntFontAtlasLoader.hpp>
#include <mvcgame/skeleton/SpineSkeletonLoader.hpp>

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
    _skeletons.setStreamManager(_assetStreams);    

    _textures.add(std::unique_ptr<PngTextureLoader>(new PngTextureLoader()), "png");

    std::unique_ptr<GdxTextureAtlasLoader> gdx(new GdxTextureAtlasLoader());
    gdx->setTextureManager(_textures);
    _textureAtlases.add(std::move(gdx), "atlas");

    std::unique_ptr<CocosTextureAtlasLoader> cocos(new CocosTextureAtlasLoader());
    cocos->setTextureManager(_textures);
    _textureAtlases.add(std::move(cocos), "plist");    

    std::unique_ptr<FntFontAtlasLoader> fnt(new FntFontAtlasLoader());
    fnt->setTextureManager(_textures);
    _fontAtlases.add(std::move(fnt), "fnt");

    std::unique_ptr<SpineSkeletonLoader> spine(new SpineSkeletonLoader());
    spine->setTextureAtlasManager(_textureAtlases);
    _skeletons.add(std::move(spine), "json");    
}

AssetManager<Skeleton>& ServiceLocator::getSkeletons()
{
    return _skeletons;
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
