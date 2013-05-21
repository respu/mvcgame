
#include "hello/controller/MainMenuOptionController.hpp"

#include <mvcgame/view/View.hpp>
#include <mvcgame/view/TextView.hpp>
#include <mvcgame/view/ColorView.hpp>
#include <mvcgame/base/Color.hpp>

const mvcgame::gunit_t MainMenuOptionController::_textSize = 40;

MainMenuOptionController::MainMenuOptionController(const std::string& text) : _text(text)
{
}

void MainMenuOptionController::controllerAdded()
{
	auto bg = std::unique_ptr<mvcgame::ColorView>(new mvcgame::ColorView());
	bg->setBackgroundColor(mvcgame::Color(0, 255, 195));
	bg->getFrame().size.width = getParent().getView().getFrame().size.width-20;
	bg->getFrame().size.height = _textSize;
	setView(std::move(bg));

	auto text = std::unique_ptr<mvcgame::TextView>(new mvcgame::TextView());
	text->setFrame(bg->getFrame());

	text->setTextFont("Arial");
	text->setTextColor(mvcgame::Color(100, 100, 100));
	text->setTextHorizontalAlign(mvcgame::TextView::HorizontalAlign::Center);
	text->setTextVerticalAlign(mvcgame::TextView::VerticalAlign::Center);
	text->setTextSize(_textSize);
	text->setText(_text);

	bg->addChild(std::move(text));
}