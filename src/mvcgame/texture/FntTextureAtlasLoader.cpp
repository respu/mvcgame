
#include <mvcgame/texture/FntTextureAtlasLoader.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>
#include <mvcgame/util/StringUtils.hpp>

#include <string>

namespace mvcgame {

    bool FntTextureAtlasLoader::validate(std::istream& input) const
    {
        return true;
    }

    std::unique_ptr<TextureAtlas> FntTextureAtlasLoader::load(std::istream& in) const
    {
        std::unique_ptr<TextureAtlas> atlas = nullptr;
        return atlas;
    }

}