
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
    std::unique_ptr<ColorView> bg(new ColorView());
    bg->setBackgroundColor(Color(0, 0, 0));
    bg->getFrame().size = getRoot().getView().getSize();
    bg->getFrame().origin = bg->getFrame().size/2;

    auto guybrushAtlas = getAssets().load<TextureAtlas>("guybrush");
    auto guybrushSheet = getAssets().loadSheet(*guybrushAtlas);
    std::unique_ptr<Sprite> guybrush(new Sprite());
    guybrush->setSheet(guybrushSheet);
    guybrush->getFrame().origin = bg->getFrame().size/2;
    guybrush->getFrame().origin.x -= 150;
    guybrush->setSpriteFrameDuration(20);

    bg->addChild(std::move(guybrush));

    std::unique_ptr<Sprite> guybrush2(new Sprite());
    guybrush2->setSheet(guybrushSheet);
    guybrush2->getFrame().origin = bg->getFrame().size/2;
    guybrush2->getFrame().origin.x += 150;
    guybrush2->setSpriteFrameDuration(20);

    bg->addChild(std::move(guybrush2));

    auto fontAtlas = getAssets().load<FontAtlas>("font");
    auto fontSheet = getAssets().loadSheet(*fontAtlas);
    std::unique_ptr<TextView> title(new TextView());
    title->setSheet(fontSheet);
    title->getFrame().size = Size(50, 50);
    title->getFrame().origin = bg->getFrame().size/2;
    title->getFrame().origin.x -= 50;
    title->getFrame().origin.y += 100;
    title->setText("mvcgame says hello!");

    bg->addChild(std::move(title));
    
    setView(std::move(bg));
}