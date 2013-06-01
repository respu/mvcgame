
#include "hello/asset/AssetsManager.hpp"

#include <mvcgame/texture/PngTextureLoader.hpp>
#include <mvcgame/texture/GdxTextureAtlasLoader.hpp>

AssetsManager::AssetsManager()
{
    addLoader<mvcgame::Texture>(std::unique_ptr<mvcgame::PngTextureLoader>(new mvcgame::PngTextureLoader()));
    addLoader<mvcgame::TextureAtlas>(std::unique_ptr<mvcgame::GdxTextureAtlasLoader>(new mvcgame::GdxTextureAtlasLoader()));
}