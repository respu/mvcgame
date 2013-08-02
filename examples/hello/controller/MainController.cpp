
#include "hello/controller/MainController.hpp"
#include "hello/base/ServiceLocator.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/View.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/texture/SpriteSheet.hpp>
#include <mvcgame/font/FontSheet.hpp>
#include <mvcgame/view/SpineSkeletonView.hpp>
#include <mvcgame/action/TweenAction.hpp>

using namespace mvcgame;

MainController::MainController()
{
}

void MainController::controllerAdded()
{
    auto bg = std::make_shared<ColorView>();
    bg->setBackgroundColor(Color(100, 100, 100));
    bg->getFrame().size = getRoot().getView().getSize();
    bg->getFrame().origin -= bg->getFrame().size/2;

    auto test = std::make_shared<ColorView>();
    test->setBackgroundColor(Colors::Red);
    test->getFrame().size = getRoot().getView().getSize()/2;
    test->getFrame().size.height /= 2;
    test->getFrame().origin -= test->getFrame().size/2;
    bg->addChild(test);

    test = std::make_shared<ColorView>();
    test->setBackgroundColor(Colors::Green);
    test->getFrame().size = getRoot().getView().getSize()/2;
    test->getFrame().size.height /= 2;
    test->getFrame().origin -= test->getFrame().size/2;
    test->setRotation(Rotation::Pi/4);
    bg->addChild(test);

    test = std::make_shared<ColorView>();
    test->setBackgroundColor(Colors::Blue);
    test->getFrame().size = getRoot().getView().getSize()/2;
    test->getFrame().size.height /= 2;
    test->getFrame().origin -= test->getFrame().size/2;
    test->setRotation(Rotation::Pi/2);
    bg->addChild(test);    

    auto guybrushAtlas = ServiceLocator::get().getTextureAtlases().load("guybrush");
    _guybrush = std::make_shared<Sprite>(*guybrushAtlas);  
    _guybrush->getFrame().origin -= _guybrush->getFrame().size/2;
    _guybrush->getFrame().origin.x -= 150;
    _guybrush->setRotation(Rotation::Pi/4);
    _guybrush->setScale(0.5);    
    _guybrush->setSpriteFrameDuration(20);
    bg->addChild(_guybrush);

    _guybrush = std::make_shared<Sprite>(*guybrushAtlas);  
    _guybrush->getFrame().origin -= _guybrush->getFrame().size/2;
    _guybrush->getFrame().origin.x -= 150;
    _guybrush->setSpriteFrameDuration(20);
    _guybrush->setScale(0.5);    
    bg->addChild(_guybrush);    

    auto miguelAtlas = ServiceLocator::get().getTextureAtlases().load("miguel");
    auto miguel = std::make_shared<Sprite>(*miguelAtlas);
    miguel->getFrame().origin -= miguel->getFrame().size/2;
    miguel->getFrame().origin.x += 150;
    miguel->setSpriteFrameDuration(20);
    bg->addChild(miguel);

    auto fontAtlas = ServiceLocator::get().getFontAtlases().load("font");
    FontSheet fontSheet(*fontAtlas);
    auto title = std::make_shared<TextView>();
    title->setSheet(fontSheet);
    title->getFrame().size = Size(50, 50);
    title->getFrame().origin -= title->getFrame().size/2;
    title->getFrame().origin.x -= 100;
    title->getFrame().origin.y += 120;
    title->setText("mvcgame says hello!");
    bg->addChild(title);

    auto spineboySkel = ServiceLocator::get().getSkeletons().load("spineboy");
    std::cout << *spineboySkel << std::endl;
    auto spineboy = std::make_shared<SpineSkeletonView>(spineboySkel);
    spineboy->getFrame().origin -= spineboy->getFrame().size/2;
    spineboy->getFrame().origin.y /= 2;
    spineboy->setScale(0.5);

    spineboySkel->setMix("walk", "jump", 0.2f);
    spineboySkel->setMix("jump", "walk", 0.4f);   
    spineboy->setAnimation("walk", true);
    spineboy->addAnimation("jump", false, 0);
    spineboy->addAnimation("walk", true, 0);
    spineboy->addAnimation("jump", false, 3);
    spineboy->addAnimation("walk", true, 0);
    spineboy->addAnimation(true, 0);
    spineboy->addAnimation("walk", true, 1);  

    bg->addChild(spineboy);    

    setView(bg);
}

void MainController::respondOnTouchStart(const TouchEvent& event)
{
    if(event.getPoints().size() == 1)
    {
        Point p = _guybrush->getInverse()*event.getPoints().front();
        std::cout << _guybrush->getTransform() << std::endl;
        std::cout << event.getPoints().front() << std::endl;
        std::cout << _guybrush->getFrame() << std::endl;
        _guybrushTouched = _guybrush->getFrame().contains(p);
        if(_guybrushTouched)
        {
            std::cout << "GUYBRUSH TOUCHED!!!" << std::endl;
            _guybrushTouchPoint = event.getPoints().front();
            _guybrushTouchPoint -= _guybrush->getFrame().origin;
        }
    }
}

void MainController::respondOnTouchUpdate(const TouchEvent& event)
{
    if(_guybrushTouched)
    {
        std::cout << "GUYBRUSH MOVED!!!" << std::endl;
        auto point = event.getPoints().front();
        point -= _guybrushTouchPoint;
        _guybrush->getFrame().origin = point;
    }
}

void MainController::respondOnTouchEnd(const TouchEvent& event)
{
    _guybrushTouched = false;
}