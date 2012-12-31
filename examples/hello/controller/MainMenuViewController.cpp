
#include "hello/controller/MainMenuViewController.hpp"

#include <mvcgame/view/View.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Color.hpp>

MainMenuViewController::MainMenuViewController()
{
}

void MainMenuViewController::controllerAdded()
{
	mvcgame::ColorView* view = new mvcgame::ColorView();
	view->setFrame(getParent().getView().getFrame());
	view->setBackgroundColor(mvcgame::Color(mvcgame::Colors::Red));	
	setView(mvcgame::IViewPtr(view));
	
	/*
	mvcgame::TextView* label = new mvcgame::TextView();
	label->setText("mvcgame test");
	label->setTextColor(mvcgame::Color::White);
	label->setTextSize(20);
	view->addChild(mvcgame::ViewPtr(label));
	*/
}