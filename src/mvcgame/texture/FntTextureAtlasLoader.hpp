
#ifndef mvcgame_FntTextureAtlasLoader_hpp
#define mvcgame_FntTextureAtlasLoader_hpp

#include <mvcgame/texture/ITextureAtlasLoader.hpp>

namespace mvcgame {

    class FntTextureAtlasLoader : public ITextureAtlasLoader
    {
    public:
        bool validate(std::istream& input) const;
        std::unique_ptr<TextureAtlas> load(std::istream& input) const;
    };
}

#endif