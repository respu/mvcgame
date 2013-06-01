

#ifndef mvcgame_ITextureAtlasLoader_hpp
#define mvcgame_ITextureAtlasLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>

namespace mvcgame {

    class ITextureAtlasLoader : public IAssetLoader<TextureAtlas>
    {
    };

}

#endif