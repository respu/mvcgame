
#include "hello/asset/AssetsManager.hpp"

#include <mvcgame/texture/PngTextureLoader.hpp>
#include <mvcgame/texture/GdxTextureAtlasLoader.hpp>
#include <mvcgame/font/FntFontAtlasLoader.hpp>

AssetsManager::AssetsManager()
{
    addLoader<mvcgame::Texture>(std::unique_ptr<mvcgame::PngTextureLoader>(new mvcgame::PngTextureLoader()), "png");
    addLoader<mvcgame::TextureAtlas>(std::unique_ptr<mvcgame::GdxTextureAtlasLoader>(new mvcgame::GdxTextureAtlasLoader()), "gdx");
    addLoader<mvcgame::FontAtlas>(std::unique_ptr<mvcgame::FntFontAtlasLoader>(new mvcgame::FntFontAtlasLoader()), "fnt");
}