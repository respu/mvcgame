#include "hello/controller/MainMenuController.hpp"

#include <mvcgame/base/Application.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/asset/AssetsManager.hpp>
#include <mvcgame/texture/FilesystemTextureLoader.hpp>
#include <mvcgame/texture/PngTextureLoader.hpp>

#include <mvcgame/platform/linux/FilesystemBridge.hpp>

#include <memory>

using namespace mvcgame;

int main(int argc, char **argv)
{
    mvcgame::Application app;

    // setup the filesystem bridge
    FilesystemBridge& fsBridge = static_cast<FilesystemBridge&>(app.getBridge().getFilesystemBridge());    
    fsBridge.setBasePath("../examples/hello/resources");

    // setup the assets manager

    FilesystemTextureLoader& fsTex = app.getAssetsManager().getFilesystemTextureLoader();
    fsTex.registerLoader(std::unique_ptr<ITextureLoader>(new PngTextureLoader()), "png");

    app.getRoot().getView().setSize(mvcgame::Size(480, 320));
    app.getRoot().addChild(std::unique_ptr<MainMenuController>(new MainMenuController()));
    app.run();
}