#include "tiled/base/Application.hpp"
#include "tiled/base/ServiceLocator.hpp"

#include <mvcgame/platform/linux/ApplicationBridge.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/RootView.hpp>

#include <mvcgame/asset/AssetStreamManager.hpp>
#include <mvcgame/asset/FileStreamLoader.hpp>

#include <memory>

int main(int argc, char **argv)
{
    std::unique_ptr<mvcgame::ApplicationBridge> bridge(new mvcgame::ApplicationBridge());
    Application app(std::move(bridge));

    // setup the assets manager
    auto& mng = ServiceLocator::get().getAssetStreams();

    std::unique_ptr<mvcgame::FileStreamLoader> fs(new mvcgame::FileStreamLoader(app.getBridge().getFilesystem()));
    fs->addPath("../examples/tiled/resources");
    mng.addLoader(std::move(fs));
    
    app.run();
}