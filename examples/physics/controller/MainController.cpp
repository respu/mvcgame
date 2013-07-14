
#include "physics/controller/MainController.hpp"
#include "physics/base/ServiceLocator.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/physics/PhysicsWorldController.hpp>

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

    auto world = std::unique_ptr<PhysicsWorldController>(new PhysicsWorldController(32));
    addChild(std::move(world));

    auto shapes = ServiceLocator::get().getPhysicsAtlases().load("shapes");

    std::cout << *shapes << std::endl;

    setView(bg);
}