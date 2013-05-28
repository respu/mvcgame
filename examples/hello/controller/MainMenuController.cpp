
#include "hello/controller/MainMenuController.hpp"
#include "hello/controller/MainMenuOptionController.hpp"

#include <mvcgame/controller/RootViewController.hpp>
#include <mvcgame/view/View.hpp>
#include <mvcgame/view/RootView.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Sprite.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/asset/AssetsManager.hpp>
#include <mvcgame/texture/Texture.hpp>
#include <mvcgame/action/TweenAction.hpp>

#include <fstream>

using namespace mvcgame;

const gunit_t MainMenuController::_titleSize = 50;

MainMenuController::MainMenuController()
{
}

void MainMenuController::controllerAdded()
{
	auto bg = std::unique_ptr<ColorView>(new ColorView());
	bg->setBackgroundColor(Color(255, 255, 195));	
	bg->getFrame().size = getRoot().getView().getSize();
	bg->getFrame().origin = bg->getFrame().size/2;

	auto square = std::unique_ptr<ColorView>(new ColorView());
	square->setBackgroundColor(Colors::Red);	
	square->setFrame(getRoot().getView().getSize());
	square->setScale(0.5);
	square->getFrame().origin = bg->getFrame().size/2;
	bg->addChild(std::move(square));

	std::shared_ptr<Texture> tftexture = getAssetsManager().loadTexture("trollface");
	auto troll = std::unique_ptr<Sprite>(new Sprite());
	troll->setTexture(tftexture);
	troll->setFrame(getRoot().getView().getSize());
	troll->setScale(Scale(0.2, 0.3));
	troll->getFrame().origin = bg->getFrame().size/2;
	troll->setRotation(Rotation::Pi/4);

	auto trollRotate = std::unique_ptr<IAction>(new TweenAction([](View& view){
		view.setRotation(-Rotation::Pi/4);
		view.getFrame().origin.x += 100;
	}));
	runAction(std::move(trollRotate), *troll, Duration::secs(10));


	bg->addChild(std::move(troll));
	
	setView(std::move(bg));

	/*
	bg->addChild(std::move(createTitleView("mvcgame test", 0)));	

	auto option = std::unique_ptr<ViewController>(new MainMenuOptionController("play"));
	addChild(std::move(option));		

	option = std::unique_ptr<ViewController>(new MainMenuOptionController("credits"));
	addChild(std::move(option));
	*/
}

std::unique_ptr<View> MainMenuController::createTitleView(const std::string& name, gunit_t y)
{
	auto title = std::unique_ptr<TextView>(new TextView());
	Rect f(getRoot().getView().getSize());

	f.origin.y = f.size.height/2-y;
	f.size.height = _titleSize*2;

	title->setFrame(f);

	title->setTextFont("Arial");
	title->setTextColor(Color(Colors::Black));
	title->setTextHorizontalAlign(TextView::HorizontalAlign::Center);
	title->setTextVerticalAlign(TextView::VerticalAlign::Center);
	title->setTextSize(_titleSize);
	title->setText(name);

	return std::move(title);
}