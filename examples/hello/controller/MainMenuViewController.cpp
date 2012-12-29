
#include "hello/controller/MainMenuViewController.hpp"

#include <mvcgame/view/View.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>

MainMenuViewController::MainMenuViewController()
{
}

void MainMenuViewController::controllerAdded()
{
	mvcgame::ColorView* view = new mvcgame::ColorView();
	setView(view);
	view->setBackgroundColor(mvcgame::Color::Red);	
	view->setFrame(getParent().getView().getFrame());

	mvcgame::TextView* label = new mvcgame::TextView();
	view->addChild(label);
	label->setText("mvcgame test");
	label->setTextColor(mvcgame::Color::White);
	label->setTextSize(20);
}