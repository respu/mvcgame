#ifndef mvcgame_AssetsManager_hpp
#define mvcgame_AssetsManager_hpp

#include <mvcgame/asset/IAssetLoader.hpp>
#include <mvcgame/texture/ITextureLoader.hpp>
#include <mvcgame/texture/Texture.hpp>

#include <memory>
#include <vector>
#include <map>

namespace mvcgame {

    class Application;

    class AssetsManager
    {
    private:
        typedef std::vector<std::unique_ptr<ITextureLoader>> TextureLoaders;
        typedef std::vector<std::unique_ptr<IAssetLoader>> AssetLoaders;

        AssetLoaders _assetLoaders;
        TextureLoaders _textureLoaders;
        Application& _app;


        bool loadTextureStream(std::istream& in, std::unique_ptr<Texture>* texture);
    public:
        AssetsManager(Application& app);

        /**
         * Registers an asset loader
         */
        void registerLoader(std::unique_ptr<IAssetLoader> loader);

        /**
         * Registers a texture loader
         */
        void registerLoader(std::unique_ptr<ITextureLoader> loader);

        /**
         * Tries to load a texture
         */
        std::unique_ptr<Texture> loadTexture(const std::string& name);
    };
}

#endif