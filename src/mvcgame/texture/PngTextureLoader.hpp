
#ifndef mvcgame_PngTextureLoader_hpp
#define mvcgame_PngTextureLoader_hpp

#include <mvcgame/texture/IStreamTextureLoader.hpp>

namespace mvcgame {

    class PngTextureLoader : public IStreamTextureLoader
    {
    public:
        bool validate(std::istream& input);
        std::unique_ptr<Texture> load(std::istream& input);
    };
}

#endif