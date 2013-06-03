
#ifndef mvcgame_PngTextureLoader_hpp
#define mvcgame_PngTextureLoader_hpp

#include <mvcgame/texture/ITextureLoader.hpp>

namespace mvcgame {

    class PngTextureLoader : public ITextureLoader
    {
    public:
        bool validate(std::istream& input) const;
        std::unique_ptr<Texture> load(std::istream& input) const;
    };
}

#endif