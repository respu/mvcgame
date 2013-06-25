

#include "hello/controller/MainController.hpp"
#include "hello/base/Application.hpp"

Application::Application(std::unique_ptr<mvcgame::IApplicationBridge> bridge) :
mvcgame::Application(std::move(bridge))
{ 
}

void Application::run()
{
    getRoot().getView().setSize(mvcgame::Size(480, 320));
    getRoot().addChild(std::unique_ptr<mvcgame::ViewController>(new MainController()));    
    mvcgame::Application::run();
}