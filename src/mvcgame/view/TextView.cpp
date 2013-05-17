#include <mvcgame/view/TextView.hpp>

namespace mvcgame {

	TextView::TextView() :
	_textHorizAlign(HorizontalAlign::Left),
	_textVertiAlign(VerticalAlign::Top),
	_textColor(Colors::White),
	_textSize(20)
	{
	}

	void TextView::setTextHorizontalAlign(HorizontalAlign align)
	{
		_textHorizAlign = align;
	}

	void TextView::setTextVerticalAlign(VerticalAlign align)
	{
		_textVertiAlign = align;
	}

	void TextView::setTextFont(const std::string& font)
	{
		_textFont = font;
	}

	void TextView::setTextSize(unsigned short size)
	{
		_textSize = size;
	}

	void TextView::setText(const std::string& text)
	{
		_text = text;
	}

	void TextView::setTextColor(const Color& color)
	{
		_textColor = color;
	}
}