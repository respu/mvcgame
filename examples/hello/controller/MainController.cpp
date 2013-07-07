
#include "hello/controller/MainController.hpp"
#include "hello/base/ServiceLocator.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/View.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/texture/SpriteSheet.hpp>
#include <mvcgame/font/FontAtlas.hpp>
#include <mvcgame/font/FontSheet.hpp>
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
    bg->getFrame().origin = bg->getFrame().size/2;

    auto guybrushAtlas = ServiceLocator::get().getTextureAtlases().load("guybrush");
    _guybrush = std::make_shared<Sprite>();
    _guybrush->setSheet(*guybrushAtlas);
    _guybrush->getFrame().origin = bg->getFrame().size/2;
    _guybrush->getFrame().origin.x -= 150;
    _guybrush->setScale(0.5);
    _guybrush->setSpriteFrameDuration(20);

    bg->addChild(_guybrush);

    auto miguelAtlas = ServiceLocator::get().getTextureAtlases().load("miguel");
    auto miguel = std::make_shared<Sprite>();
    miguel->setSheet(*miguelAtlas);
    miguel->getFrame().origin = bg->getFrame().size/2;
    miguel->getFrame().origin.x += 150;
    miguel->setSpriteFrameDuration(20);

    bg->addChild(miguel);

    auto fontAtlas = ServiceLocator::get().getFontAtlases().load("font");
    FontSheet fontSheet(*fontAtlas);
    auto title = std::make_shared<TextView>();
    title->setSheet(fontSheet);
    title->getFrame().size = Size(50, 50);
    title->getFrame().origin = bg->getFrame().size/2;
    title->getFrame().origin.x -= 50;
    title->getFrame().origin.y += 100;
    title->setText("mvcgame says hello!");

    bg->addChild(title);

    auto spineboySkel = ServiceLocator::get().getSkeletons().load("spineboy");
    std::cout << *spineboySkel << std::endl;

    setView(bg);
}

void MainController::respondOnTouchStart(const TouchEvent& event)
{
    std::cout << "GUYBRUSH" << std::endl;
    _guybrushTouched = event.touched(*_guybrush);
    if(_guybrushTouched)
    {
        std::cout << "GUYBRUSH TOUCHED!!!" << std::endl;
        _guybrushTouchPoint = event.getTouchPoint(*_guybrush);
        _guybrushTouchPoint -= _guybrush->getFrame().origin;
    }
}

void MainController::respondOnTouchUpdate(const TouchEvent& event)
{
    if(_guybrushTouched)
    {
        std::cout << "GUYBRUSH MOVED!!!" << std::endl;
        auto point = event.getTouchPoint(*_guybrush);
        point -= _guybrushTouchPoint;
        _guybrush->getFrame().origin = point;
    }
}

void MainController::respondOnTouchEnd(const TouchEvent& event)
{
    _guybrushTouched = false;
}