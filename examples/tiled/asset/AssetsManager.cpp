
#include "tiled/asset/AssetsManager.hpp"

#include <mvcgame/texture/PngTextureLoader.hpp>
#include <mvcgame/tile/TmxTileMapLoader.hpp>

AssetsManager::AssetsManager()
{
    addLoader<mvcgame::Texture>(std::unique_ptr<mvcgame::PngTextureLoader>(new mvcgame::PngTextureLoader()), "png");

    std::unique_ptr<mvcgame::TmxTileMapLoader> tmx(new mvcgame::TmxTileMapLoader());
    tmx->setSourceLoader(*this);
    addLoader<mvcgame::TileMap>(std::move(tmx), "tmx");
}