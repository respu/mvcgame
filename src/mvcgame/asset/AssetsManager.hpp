#ifndef mvcgame_AssetsManager_hpp
#define mvcgame_AssetsManager_hpp

#include <mvcgame/asset/BaseAssetsManager.hpp>
#include <mvcgame/asset/AssetTypeManager.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>

namespace mvcgame {

    class AssetsManager : public BaseAssetsManager
    {
    private:
        AssetTypeManager<Texture> _textures;
        AssetTypeManager<TextureAtlas> _textureAtlases;

    public:
        AssetsManager();
        virtual ~AssetsManager();

        template<typename Asset>
        void addLoader(std::unique_ptr<IAssetLoader<Asset>> loader, const std::string& tag="");

        template<typename Asset>
        std::unique_ptr<Asset> load(const std::string& name);
    };
}

#endif