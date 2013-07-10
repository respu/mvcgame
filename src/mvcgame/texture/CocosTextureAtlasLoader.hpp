
#ifndef mvcgame_CocosTextureAtlasLoader_hpp
#define mvcgame_CocosTextureAtlasLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>

namespace mvcgame {

    class TextureAtlas;
    class Texture;
    template<typename Asset>
    class AssetManager;

    class CocosTextureAtlasLoader : public IAssetLoader<TextureAtlas>
    {
    private:
        AssetManager<Texture>* _textureManager;        
    public:
        CocosTextureAtlasLoader();

        bool validate(std::istream& input) const;
        std::shared_ptr<TextureAtlas> load(std::istream& input) const;

        /**
         * Set the assets manager to load related textures
         */        
        void setTextureManager(AssetManager<Texture>& mng);
    };
}

#endif