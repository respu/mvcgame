
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
	view->setBackgroundColor(mvcgame::Color(mvcgame::Colors::Red));
	view->setFrame(getParent().getView().getFrame());
	setView(mvcgame::ViewPtr(view));
	
	/*
	mvcgame::TextView* label = new mvcgame::TextView();
	label->setText("mvcgame test");
	label->setTextColor(mvcgame::Color::White);
	label->setTextSize(20);
	view->addChild(mvcgame::ViewPtr(label));
	*/
}