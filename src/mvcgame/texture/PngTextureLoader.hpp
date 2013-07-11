
#ifndef mvcgame_PngTextureLoader_hpp
#define mvcgame_PngTextureLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>

namespace mvcgame {

    class Texture;

    class PngTextureLoader : public IAssetLoader<Texture>
    {
    public:
        bool validate(std::istream& input) const;
        std::shared_ptr<Texture> load(std::istream& input) const;
    };
}

#endif