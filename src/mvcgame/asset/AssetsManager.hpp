#ifndef mvcgame_AssetsManager_hpp
#define mvcgame_AssetsManager_hpp

#include <mvcgame/asset/BaseAssetsManager.hpp>
#include <mvcgame/asset/AssetTypeManager.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/texture/TextureAtlas.hpp>
#include <mvcgame/texture/SpriteSheet.hpp>
#include <mvcgame/font/FontAtlas.hpp>
#include <mvcgame/font/FontSheet.hpp>
#include <mvcgame/tile/TileMap.hpp>

namespace mvcgame {

    class AssetsManager : public BaseAssetsManager
    {
    private:
        AssetTypeManager<Texture> _textures;
        AssetTypeManager<TextureAtlas> _textureAtlases;
        AssetTypeManager<FontAtlas> _fontAtlases;
        AssetTypeManager<TileMap> _tileMaps;

    public:
        AssetsManager();
        virtual ~AssetsManager();

        template<typename Asset>
        void addLoader(std::unique_ptr<IAssetLoader<Asset>> loader, const std::string& tag="");

        template<typename Asset>
        std::shared_ptr<Asset> load(const std::string& name);

        SpriteSheet loadSheet(const TextureAtlas& atlas);
        FontSheet loadSheet(const FontAtlas& atlas);
    };
}

#endif