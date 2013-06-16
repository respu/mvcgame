
#include "hello/controller/MainController.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/View.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/asset/AssetsManager.hpp>
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
    bg->setBackgroundColor(Color(0, 0, 0));
    bg->getFrame().size = getRoot().getView().getSize();
    bg->getFrame().origin = bg->getFrame().size/2;

    auto guybrushAtlas = getAssets().load<TextureAtlas>("guybrush");
    auto guybrushSheet = getAssets().loadSheet(*guybrushAtlas);
    _guybrush = std::make_shared<Sprite>();
    _guybrush->setSheet(guybrushSheet);
    _guybrush->getFrame().origin = bg->getFrame().size/2;
    _guybrush->getFrame().origin.x -= 150;
    _guybrush->setSpriteFrameDuration(20);

    bg->addChild(_guybrush);

    auto guybrush2 = std::make_shared<Sprite>();
    guybrush2->setSheet(guybrushSheet);
    guybrush2->getFrame().origin = bg->getFrame().size/2;
    guybrush2->getFrame().origin.x += 150;
    guybrush2->setSpriteFrameDuration(20);

    bg->addChild(guybrush2);

    auto fontAtlas = getAssets().load<FontAtlas>("font");
    auto fontSheet = getAssets().loadSheet(*fontAtlas);
    auto title = std::make_shared<TextView>();
    title->setSheet(fontSheet);
    title->getFrame().size = Size(50, 50);
    title->getFrame().origin = bg->getFrame().size/2;
    title->getFrame().origin.x -= 50;
    title->getFrame().origin.y += 100;
    title->setText("mvcgame says hello!");

    bg->addChild(title);
    
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