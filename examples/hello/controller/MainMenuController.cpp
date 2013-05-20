
#include "hello/controller/MainMenuController.hpp"
#include "hello/controller/MainMenuOptionController.hpp"

#include <mvcgame/view/View.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/base/Color.hpp>

const mvcgame::gunit_t MainMenuController::_titleSize = 50;

MainMenuController::MainMenuController()
{
}

void MainMenuController::controllerAdded()
{
	auto bg = std::unique_ptr<mvcgame::ColorView>(new mvcgame::ColorView());

	bg->setBackgroundColor(mvcgame::Color(255, 255, 195));	
	bg->setFrame(getParent().getView().getFrame());
	
	setView(std::move(bg));
	
	bg->addChild(std::move(createTitleView("mvcgame test", 0)));	

	auto option = std::unique_ptr<mvcgame::ViewController>(new MainMenuOptionController("play"));
	addChild(std::move(option));		

	option = std::unique_ptr<mvcgame::ViewController>(new MainMenuOptionController("credits"));
	addChild(std::move(option));
}

std::unique_ptr<mvcgame::View> MainMenuController::createTitleView(const std::string& name, mvcgame::gunit_t y)
{
	auto title = std::unique_ptr<mvcgame::TextView>(new mvcgame::TextView());
	mvcgame::Rect f(getParent().getView().getFrame());

	f.origin.y = f.size.height/2-y;
	f.size.height = _titleSize*2;

	title->setParentAnchor(mvcgame::Anchor(0.5, 1));
	title->setFrame(f);

	title->setTextFont("Arial");
	title->setTextColor(mvcgame::Color(mvcgame::Colors::Black));
	title->setTextHorizontalAlign(mvcgame::TextView::HorizontalAlign::Center);
	title->setTextVerticalAlign(mvcgame::TextView::VerticalAlign::Center);
	title->setTextSize(_titleSize);
	title->setText(name);

	return std::move(title);
}