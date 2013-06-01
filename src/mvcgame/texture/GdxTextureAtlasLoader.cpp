
#include <mvcgame/texture/GdxTextureAtlasLoader.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>

namespace mvcgame {

    bool GdxTextureAtlasLoader::validate(std::istream& input)
    {
        return false;
    }

    std::unique_ptr<TextureAtlas> GdxTextureAtlasLoader::load(std::istream& input)
    {
        return std::unique_ptr<TextureAtlas>();
    }

}