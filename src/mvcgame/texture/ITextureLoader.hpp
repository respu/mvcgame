

#ifndef mvcgame_ITextureLoader_hpp
#define mvcgame_ITextureLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>
#include <mvcgame/texture/Texture.hpp>

namespace mvcgame {

    class ITextureLoader : public IAssetLoader<Texture>
    {

    };
}

#endif