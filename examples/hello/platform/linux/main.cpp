
#include "hello/platform/linux/main.h"
#include "hello/controller/MainMenuViewController.hpp"
#include <mvcgame/Application.hpp>
#include <memory>

int main(int argc, char **argv)
{
    mvcgame::Application app;
    app.setSize(mvcgame::Size(480, 320));
    app.setRootViewController(std::unique_ptr<mvcgame::IViewController>(new MainMenuViewController()));
    app.run();
}