
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
#include <mvcgame/texture/FontAtlas.hpp>
#include <mvcgame/action/TweenAction.hpp>

#include <fstream>

using namespace mvcgame;

const gunit_t MainController::_titleSize = 50;

MainController::MainController()
{
}

void MainController::controllerAdded()
{
	auto bg = std::unique_ptr<ColorView>(new ColorView());
	bg->setBackgroundColor(Color(255, 255, 195));	
	bg->getFrame().size = getRoot().getView().getSize();
	bg->getFrame().origin = bg->getFrame().size/2;

	auto guybrushAtlas = getAssets().load<TextureAtlas>("guybrush");
	std::shared_ptr<Texture> guybrushTexture = getAssets().load<Texture>(guybrushAtlas->getTextureName());
	std::shared_ptr<SpriteSheet> guybrushSheet(new SpriteSheet(guybrushTexture, *guybrushAtlas));

	std::unique_ptr<Sprite> guybrush(new Sprite());
	guybrush->setSheet(guybrushSheet);
	guybrush->getFrame().size = guybrushSheet->getSize();
	guybrush->getFrame().origin = bg->getFrame().size/2;
	guybrush->getFrame().origin.x -= 150;
	guybrush->setSpriteFrameDuration(20);

	bg->addChild(std::move(guybrush));

	std::unique_ptr<Sprite> guybrush2(new Sprite());
	guybrush2->setSheet(guybrushSheet);
	guybrush2->getFrame().size = guybrushSheet->getSize();
	guybrush2->getFrame().origin = bg->getFrame().size/2;
	guybrush2->getFrame().origin.x += 150;
	guybrush2->setSpriteFrameDuration(20);

	bg->addChild(std::move(guybrush2));

	auto fontAtlas = getAssets().load<FontAtlas>("font");
	std::unique_ptr<TextView> title(new TextView());

	bg->addChild(std::move(title));
	
	setView(std::move(bg));
}