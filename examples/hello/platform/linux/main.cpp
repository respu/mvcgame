#include "hello/base/Application.hpp"

#include <mvcgame/platform/linux/ApplicationBridge.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/RootView.hpp>

#include <mvcgame/asset/AssetsManager.hpp>
#include <mvcgame/asset/FileStreamLoader.hpp>

#include <memory>

int main(int argc, char **argv)
{
    std::unique_ptr<mvcgame::ApplicationBridge> bridge(new mvcgame::ApplicationBridge());
    Application app(std::move(bridge));

    // setup the assets manager
    std::unique_ptr<mvcgame::FileStreamLoader> fs(new mvcgame::FileStreamLoader(app.getBridge().getFilesystem()));
    fs->addPath("../examples/hello/resources");
    app.getAssets().addStreamLoader(std::move(fs));
    
    app.run();
}