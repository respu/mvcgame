
#include "hello/controller/MainMenuViewController.hpp"

#include <mvcgame/view/View.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Color.hpp>
#include <mvcgame/Geometry.hpp>

MainMenuViewController::MainMenuViewController()
{
}

void MainMenuViewController::controllerAdded()
{
	mvcgame::ColorView* bg = new mvcgame::ColorView();
	bg->setBackgroundColor(mvcgame::Color(255, 255, 195));	
	bg->setFrame(getParent().getView().getFrame());
	setView(mvcgame::IViewPtr(bg));
	
	bg->addChild(std::move(createTitleView("mvcgame test", 0)));

	bg->addChild(std::move(createOptionView("play", 100)));
	bg->addChild(std::move(createOptionView("credits", 150)));
}

mvcgame::IViewPtr MainMenuViewController::createTitleView(const std::string& name, mvcgame::gunit_t y)
{
	mvcgame::TextView* title = new mvcgame::TextView();
	mvcgame::Rect f(getParent().getView().getFrame());
	f.origin.y = f.size.height/2-y;
	f.size.height = _titleSize/2;	
	title->setFrame(f);
	title->setAnchor(mvcgame::Anchor(0.5, 1));

	title->setTextFont("Arial");
	title->setTextColor(mvcgame::Color(mvcgame::Colors::Black));
	title->setTextHorizontalAlign(mvcgame::ITextView::HorizontalAlign::Center);
	title->setTextVerticalAlign(mvcgame::ITextView::VerticalAlign::Center);
	title->setTextSize(_titleSize);
	title->setText(name);

	return mvcgame::IViewPtr(title);
}

mvcgame::IViewPtr MainMenuViewController::createOptionView(const std::string& name, mvcgame::gunit_t y)
{
	mvcgame::TextView* option = new mvcgame::TextView();
	mvcgame::Rect f(getParent().getView().getFrame());
	f.origin.y = f.size.height/2-y;
	f.size.height = _optionSize/2;	
	option->setFrame(f);
	option->setAnchor(mvcgame::Anchor(0.5, 1));

	option->setTextFont("Arial");
	option->setTextColor(mvcgame::Color(100, 100, 100));
	option->setTextHorizontalAlign(mvcgame::ITextView::HorizontalAlign::Center);
	option->setTextVerticalAlign(mvcgame::ITextView::VerticalAlign::Center);
	option->setTextSize(_optionSize);
	option->setText(name);

	return mvcgame::IViewPtr(option);
}