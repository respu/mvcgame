

#include <mvcgame/asset/AssetsManager.hpp>
#include <mvcgame/platform/IApplicationBridge.hpp>
#include <mvcgame/base/Application.hpp>

namespace mvcgame {

    AssetsManager::AssetsManager(Application& app) :
    _app(app), _fsTextureLoader(app.getBridge().getFilesystem())
    {

    }

    FilesystemTextureLoader& AssetsManager::getFilesystemTextureLoader()
    {
        return _fsTextureLoader;
    }

    const FilesystemTextureLoader& AssetsManager::getFilesystemTextureLoader() const
    {
        return _fsTextureLoader;
    }

    std::unique_ptr<Texture> AssetsManager::loadTexture(const std::string& name)
    {
        return _fsTextureLoader.load(name);
    }

}