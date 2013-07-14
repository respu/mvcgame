
#include "physics/controller/MainController.hpp"
#include "physics/base/ServiceLocator.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/physics/PhysicsWorldController.hpp>
#include <mvcgame/physics/PhysicsBodyController.hpp>

#include <Box2D/Box2D.h>

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

    auto world = std::unique_ptr<PhysicsWorldController>(new PhysicsWorldController(64));

    auto groundView = std::make_shared<ColorView>();
    groundView->setBackgroundColor(Color(0, 0, 0));
    groundView->getFrame().size.width= 250;
    groundView->getFrame().size.height = 50;
    groundView->getFrame().origin.x = bg->getFrame().origin.x;
    groundView->setAnchor(Anchor(0.5, 0));
    b2BodyDef* groundDef = new b2BodyDef();
    auto& groundCtrl = world->createBody(groundDef);
    groundCtrl.setView(groundView);
    b2FixtureDef* groundFixDef = new b2FixtureDef();
    groundFixDef->density = 0.1f;
    groundFixDef->friction = 1.0f;
    groundCtrl.addFixture(groundFixDef);

    auto hamburgerTexture = ServiceLocator::get().getTextures().load("hamburger"); 
    PhysicsBodyController* hamburgerCtrl = nullptr;
    unsigned hamburgerNum = 4;
    for(unsigned i=0; i<hamburgerNum; i++)
    {
        auto hamburgerView = std::make_shared<Sprite>(hamburgerTexture);        
        hamburgerCtrl = &world->createBody();
        hamburgerView->getFrame().origin = bg->getFrame().size;
        hamburgerView->getFrame().origin.x *= (float)i/hamburgerNum;
        hamburgerView->getFrame().origin.x += hamburgerView->getFrame().size.width/2;
        std::cout << hamburgerView->getFrame() << std::endl;
        hamburgerCtrl->setView(hamburgerView);
        b2FixtureDef* hamburgerFixDef = new b2FixtureDef();
        hamburgerFixDef->density = 0.1f;
        hamburgerFixDef->friction = 0.3f;
        hamburgerCtrl->addFixture(hamburgerFixDef);
    }

    setView(bg);

    addChild(std::move(world));
}