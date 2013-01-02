
#include "hello/controller/MainMenuOptionController.hpp"

#include <mvcgame/view/View.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/view/Color.hpp>
#include <mvcgame/Geometry.hpp>

MainMenuOptionController::MainMenuOptionController(const std::string& text) : _text(text)
{
}

void MainMenuOptionController::controllerAdded()
{
	mvcgame::ColorView* bg = new mvcgame::ColorView();
	bg->setBackgroundColor(mvcgame::Color(0, 255, 195));
	bg->getFrame().size.width = getParent().getView().getFrame().size.width-20;
	bg->getFrame().size.height = _textSize;
	bg->getParentAnchor().y = 1;
	setView(mvcgame::IViewPtr(bg));

	mvcgame::TextView* text = new mvcgame::TextView();
	text->setFrame(bg->getFrame());

	text->setTextFont("Arial");
	text->setTextColor(mvcgame::Color(100, 100, 100));
	text->setTextHorizontalAlign(mvcgame::ITextView::HorizontalAlign::Center);
	text->setTextVerticalAlign(mvcgame::ITextView::VerticalAlign::Center);
	text->setTextSize(_textSize);
	text->setText(_text);

	bg->addChild(mvcgame::IViewPtr(text));
}