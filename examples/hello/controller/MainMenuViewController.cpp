
#include "hello/controller/MainMenuViewController.hpp"

#include <mvcgame/view/View.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>

MainMenuViewController::MainMenuViewController()
{
	setView(new mvcgame::View());

	mvcgame::TextView* label = new mvcgame::TextView();

	label->setText("mvcgame test");
	label->setTextColor(mvcgame::Color::White);
	label->setTextSize(20);

	getView().addChild(label);
}