#include "hello/controller/MainMenuController.hpp"

#include <mvcgame/Application.hpp>
#include <mvcgame/Pointers.hpp>

#include <memory>

int main(int argc, char **argv)
{
    mvcgame::Application app;
    app.setSize(mvcgame::Size(480, 320));
    app.setViewController(mvcgame::IViewControllerPtr(new MainMenuController()));
    app.run();
}