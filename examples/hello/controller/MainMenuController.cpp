
#include "hello/controller/MainMenuController.hpp"
#include "hello/controller/MainMenuOptionController.hpp"

#include <mvcgame/view/View.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Color.hpp>
#include <mvcgame/Geometry.hpp>

MainMenuController::MainMenuController()
{
}

void MainMenuController::controllerAdded()
{
	mvcgame::ColorView* bg = new mvcgame::ColorView();

	bg->setBackgroundColor(mvcgame::Color(255, 255, 195));	
	bg->setFrame(getParent().getView().getFrame());
	
	setView(mvcgame::IViewPtr(bg));
	
	bg->addChild(std::move(createTitleView("mvcgame test", 0)));	

	MainMenuOptionController* option = nullptr;

	option = new MainMenuOptionController("play");
	addChild(mvcgame::IViewControllerPtr(option));		

	option = new MainMenuOptionController("credits");
	addChild(mvcgame::IViewControllerPtr(option));	
}

mvcgame::IViewPtr MainMenuController::createTitleView(const std::string& name, mvcgame::gunit_t y)
{
	mvcgame::TextView* title = new mvcgame::TextView();
	mvcgame::Rect f(getParent().getView().getFrame());

	f.origin.y = f.size.height/2-y;
	f.size.height = _titleSize*2;

	title->setParentAnchor(mvcgame::Anchor(0.5, 1));
	title->setFrame(f);

	title->setTextFont("Arial");
	title->setTextColor(mvcgame::Color(mvcgame::Colors::Black));
	title->setTextHorizontalAlign(mvcgame::ITextView::HorizontalAlign::Center);
	title->setTextVerticalAlign(mvcgame::ITextView::VerticalAlign::Center);
	title->setTextSize(_titleSize);
	title->setText(name);

	return mvcgame::IViewPtr(title);
}