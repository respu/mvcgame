#include "hello/controller/MainMenuController.hpp"

#include <mvcgame/base/Application.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/asset/AssetsManager.hpp>
#include <mvcgame/texture/FilesystemTextureLoader.hpp>
#include <mvcgame/texture/PngTextureLoader.hpp>

#include <mvcgame/platform/linux/ApplicationBridge.hpp>

#include <memory>

using namespace mvcgame;

int main(int argc, char **argv)
{
    std::unique_ptr<ApplicationBridge> bridge(new ApplicationBridge());
    mvcgame::Application app(std::move(bridge));

    // setup the assets manager
     std::unique_ptr<FilesystemTextureLoader> fsTex(new FilesystemTextureLoader(app.getBridge().getFilesystem()));
    fsTex->registerLoader(std::unique_ptr<IStreamTextureLoader>(new PngTextureLoader()), "png");
    fsTex->addPath("../examples/hello/resources");
    app.getAssetsManager().registerLoader(std::move(fsTex));

    app.getRoot().getView().setSize(mvcgame::Size(480, 320));
    app.getRoot().addChild(std::unique_ptr<MainMenuController>(new MainMenuController()));
    app.run();
}