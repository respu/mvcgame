
#include "physics/controller/MainController.hpp"
#include "physics/base/ServiceLocator.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/physics/PhysicsWorldController.hpp>
#include <mvcgame/physics/PhysicsBodyController.hpp>

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

    auto world = std::unique_ptr<PhysicsWorldController>(new PhysicsWorldController(32));

    auto shapes = ServiceLocator::get().getPhysicsAtlases().load("shapes");
    std::cout << *shapes << std::endl;

    auto hamburgerTexture = ServiceLocator::get().getTextures().load("hamburger");
    auto hamburgerCtrl = std::unique_ptr<PhysicsBodyController>(new PhysicsBodyController());
    auto hamburgetView = std::make_shared<Sprite>(hamburgerTexture);
    hamburgerCtrl->setView(hamburgetView);
    hamburgerCtrl->setShape(shapes->getShape("hamburger"));
    world->addBody(std::move(hamburgerCtrl));

    hamburgetView->getFrame().origin = bg->getFrame().size/2;

    addChild(std::move(world));
}