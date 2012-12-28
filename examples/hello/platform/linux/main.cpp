
#include "hello/platform/linux/main.h"
#include "hello/MainMenuViewController.hpp"
#include <mvcgame/Application.hpp>

int main(int argc, char **argv)
{
    mvcgame::Application app;
    app.setRootViewController(new MainMenuViewController());
    app.run();
}