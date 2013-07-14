#include "physics/base/Application.hpp"
#include "physics/base/ServiceLocator.hpp"

#include <mvcgame/platform/linux/ApplicationBridge.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/asset/FileStreamLoader.hpp>

#include <memory>

int main(int argc, char **argv)
{
    std::unique_ptr<mvcgame::ApplicationBridge> bridge(new mvcgame::ApplicationBridge());
    Application app(std::move(bridge));

    // setup the asset stream manager
    auto& mng = ServiceLocator::get().getAssetStreams();

    std::unique_ptr<mvcgame::FileStreamLoader> fs(new mvcgame::FileStreamLoader(app.getBridge().getFilesystem()));
    fs->addPath("../examples/physics/resources");
    mng.addLoader(std::move(fs));
    
    app.run();
}