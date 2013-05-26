#ifndef mvcgame_AssetsManager_hpp
#define mvcgame_AssetsManager_hpp

#include <mvcgame/texture/FilesystemTextureLoader.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <memory>

namespace mvcgame {

    class Application;

    class AssetsManager
    {
    private:
        Application& _app;
        FilesystemTextureLoader _fsTextureLoader;
    public:
        AssetsManager(Application& app);
        FilesystemTextureLoader& getFilesystemTextureLoader();
        const FilesystemTextureLoader& getFilesystemTextureLoader() const;

        std::unique_ptr<Texture> loadTexture(const std::string& name);
    };
}

#endif