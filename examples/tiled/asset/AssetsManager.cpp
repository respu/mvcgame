
#include "tiled/asset/AssetsManager.hpp"

#include <mvcgame/texture/PngTextureLoader.hpp>
#include <mvcgame/tile/TmxTileMapLoader.hpp>

AssetsManager::AssetsManager()
{
    addLoader<mvcgame::Texture>(std::unique_ptr<mvcgame::PngTextureLoader>(new mvcgame::PngTextureLoader()), "png");
    addLoader<mvcgame::TileMap>(std::unique_ptr<mvcgame::TmxTileMapLoader>(new mvcgame::TmxTileMapLoader()), "tmx");
}