

#ifndef mvcgame_ITextureAtlasLoader_hpp
#define mvcgame_ITextureAtlasLoader_hpp

namespace mvcgame {

    class Texture;

    class ITextureAtlasLoader
    {
    public:
        virtual ~ITextureAtlasLoader(){};
        
        virtual load(TextureAtlas& atlas) = 0;
    };

}

#endif