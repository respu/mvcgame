
#ifndef mvcgame_GdxTextureAtlasLoader_hpp
#define mvcgame_GdxTextureAtlasLoader_hpp

#include <mvcgame/texture/ITextureAtlasLoader.hpp>

namespace mvcgame {

    class GdxTextureAtlasLoader : public ITextureAtlasLoader
    {
    public:
        const std::string& getTag() const;
        bool validate(std::istream& input);
        std::unique_ptr<TextureAtlas> load(std::istream& input);
    };
}

#endif