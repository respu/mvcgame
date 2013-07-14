
#include "physics/controller/MainController.hpp"
#include "physics/base/ServiceLocator.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/ColorView.hpp>

using namespace mvcgame;

MainController::MainController()
{
}

void MainController::controllerAdded()
{
    auto bg = std::make_shared<ColorView>();
    bg->setBackgroundColor(Color(100, 100, 100));
    bg->getFrame().size = getRoot().getView().getSize();
    bg->getFrame().origin = bg->getFrame().size/2;

    setView(bg);
}