
#ifndef mvcgame_PngTextureLoader_hpp
#define mvcgame_PngTextureLoader_hpp

#include <mvcgame/texture/ITextureLoader.hpp>

namespace mvcgame {

    class PngTextureLoader : public ITextureLoader
    {
    public:
        const std::string& getTag() const;
        bool validate(std::istream& input);
        std::unique_ptr<Texture> load(std::istream& input);
    };
}

#endif