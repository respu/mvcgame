#include "hello/controller/MainMenuController.hpp"

#include <mvcgame/base/Application.hpp>

#include <memory>

int main(int argc, char **argv)
{
    mvcgame::Application app;
    app.setSize(mvcgame::Size(480, 320));
    app.setViewController(std::unique_ptr<mvcgame::ViewController>(new MainMenuController()));
    app.run();
}