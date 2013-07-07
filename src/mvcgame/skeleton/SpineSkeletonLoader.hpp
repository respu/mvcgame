#ifndef mvcgame_SpineSkeletonLoader_hpp
#define mvcgame_SpineSkeletonLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>

namespace mvcgame {

    class TextureAtlas;
    class Skeleton;
    template<typename Asset>
    class AssetManager;

    class SpineSkeletonLoader : public IAssetLoader<Skeleton>
    {
    private:
        AssetManager<TextureAtlas>* _textureAtlasManager;        
    public:
        SpineSkeletonLoader();

        bool validate(std::istream& input) const;
        std::unique_ptr<Skeleton> load(std::istream& input) const;

        /**
         * Set the assets manager to load related textures
         */        
        void setTextureAtlasManager(AssetManager<TextureAtlas>& mng);

    };

}

#endif