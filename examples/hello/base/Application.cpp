

#include "hello/controller/MainMenuController.hpp"
#include "hello/base/Application.hpp"

Application::Application(std::unique_ptr<mvcgame::IApplicationBridge> bridge) :
mvcgame::Application(std::move(bridge))
{ 
}

const AssetsManager& Application::getAssets() const
{
    return _assets;
}

AssetsManager& Application::getAssets()
{
    return _assets;
}

void Application::run()
{
    getRoot().getView().setSize(mvcgame::Size(480, 320));
    getRoot().addChild(std::unique_ptr<mvcgame::ViewController>(new MainMenuController()));    
    mvcgame::Application::run();
}