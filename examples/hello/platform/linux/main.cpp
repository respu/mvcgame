#include "hello/controller/MainMenuController.hpp"

#include <mvcgame/base/Application.hpp>
#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/RootView.hpp>

#include <memory>

int main(int argc, char **argv)
{
    mvcgame::Application app;
    app.getRoot().getView().setSize(mvcgame::Size(480, 320));
    app.getRoot().addChild(std::unique_ptr<MainMenuController>(new MainMenuController()));
    app.run();
}