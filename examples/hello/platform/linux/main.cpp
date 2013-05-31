#include "hello/controller/MainMenuController.hpp"

#include <mvcgame/base/Application.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/asset/AssetsManager.hpp>
#include <mvcgame/asset/FilesystemAssetLoader.hpp>
#include <mvcgame/texture/PngTextureLoader.hpp>

#include <mvcgame/platform/linux/ApplicationBridge.hpp>

#include <memory>

using namespace mvcgame;

int main(int argc, char **argv)
{
    std::unique_ptr<ApplicationBridge> bridge(new ApplicationBridge());
    mvcgame::Application app(std::move(bridge));

    // setup the assets manager
    std::unique_ptr<FilesystemAssetLoader> fs(new FilesystemAssetLoader(app.getBridge().getFilesystem()));
    fs->addPath("../examples/hello/resources");
    app.getAssetsManager().registerLoader(std::move(fs));
    app.getAssetsManager().registerLoader(std::unique_ptr<ITextureLoader>(new PngTextureLoader()));

    app.getRoot().getView().setSize(mvcgame::Size(480, 320));
    app.getRoot().addChild(std::unique_ptr<MainMenuController>(new MainMenuController()));
    app.run();
}