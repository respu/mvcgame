
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
	view->setBackgroundColor(mvcgame::Color::Red);	
	view->setFrame(getParent().getView().getFrame());
	setView(mvcgame::IViewPtr(view));	

	mvcgame::TextView* label = new mvcgame::TextView();
	label->setText("mvcgame test");
	label->setTextColor(mvcgame::Color::White);
	label->setTextSize(20);
	view->addChild(mvcgame::IViewPtr(label));	
}