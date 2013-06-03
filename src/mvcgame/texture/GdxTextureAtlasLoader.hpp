
#ifndef mvcgame_GdxTextureAtlasLoader_hpp
#define mvcgame_GdxTextureAtlasLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>

namespace mvcgame {

    class TextureAtlas;

    class GdxTextureAtlasLoader : public IAssetLoader<TextureAtlas>
    {
    public:
        bool validate(std::istream& input) const;
        std::unique_ptr<TextureAtlas> load(std::istream& input) const;
    };
}

#endif