
#ifndef mvcgame_examples_physics_ServiceLocator_hpp
#define mvcgame_examples_physics_ServiceLocator_hpp

#include <mvcgame/asset/AssetManager.hpp>
#include <mvcgame/asset/AssetStreamManager.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>
#include <mvcgame/font/FontAtlas.hpp>

class ServiceLocator
{
private:
    mvcgame::AssetStreamManager _assetStreams;
    mvcgame::AssetManager<mvcgame::Texture> _textures;
    mvcgame::AssetManager<mvcgame::TextureAtlas> _textureAtlases;
    mvcgame::AssetManager<mvcgame::FontAtlas> _fontAtlases;


    ServiceLocator();
    ServiceLocator(const ServiceLocator& other);
public:

    static ServiceLocator& get();

    mvcgame::AssetStreamManager& getAssetStreams();
    mvcgame::AssetManager<mvcgame::Texture>& getTextures();
    mvcgame::AssetManager<mvcgame::TextureAtlas>& getTextureAtlases();
    mvcgame::AssetManager<mvcgame::FontAtlas>& getFontAtlases();
};

#endif