#ifndef mvcgame_AssetsManager_hpp
#define mvcgame_AssetsManager_hpp

#include <mvcgame/texture/INameTextureLoader.hpp>
#include <mvcgame/texture/Texture.hpp>

#include <memory>
#include <vector>

namespace mvcgame {

    class Application;

    class AssetsManager
    {
    private:
        typedef std::vector<std::unique_ptr<INameTextureLoader>> TextureLoaders;
        TextureLoaders _textureLoaders;
        Application& _app;
    public:
        AssetsManager(Application& app);

        void registerLoader(std::unique_ptr<INameTextureLoader> loader);

        std::unique_ptr<Texture> loadTexture(const std::string& name);
    };
}

#endif