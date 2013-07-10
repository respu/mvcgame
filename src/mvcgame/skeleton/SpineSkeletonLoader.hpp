#ifndef mvcgame_SpineSkeletonLoader_hpp
#define mvcgame_SpineSkeletonLoader_hpp

#include <mvcgame/asset/IAssetLoader.hpp>

namespace mvcgame {

    class TextureAtlas;
    class SpineSkeleton;
    template<typename Asset>
    class AssetManager;

    class SpineSkeletonLoader : public IAssetLoader<SpineSkeleton>
    {
    private:
        AssetManager<TextureAtlas>* _textureAtlasManager;        
    public:
        SpineSkeletonLoader();

        bool validate(std::istream& input) const;
        std::unique_ptr<SpineSkeleton> load(std::istream& input) const;

        /**
         * Set the assets manager to load related textures
         */        
        void setTextureAtlasManager(AssetManager<TextureAtlas>& mng);

    };

}

#endif