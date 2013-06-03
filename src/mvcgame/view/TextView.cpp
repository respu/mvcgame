#include <mvcgame/view/TextView.hpp>

namespace mvcgame {

	TextView::TextView() :
	_horizAlign(HorizontalAlign::Left),
	_vertiAlign(VerticalAlign::Top),
	_textSize(20)
	{
	}

	void TextView::setHorizontalAlign(HorizontalAlign align)
	{
		_horizAlign = align;
	}

	void TextView::setVerticalAlign(VerticalAlign align)
	{
		_vertiAlign = align;
	}

	void TextView::setFont(std::shared_ptr<Font> font)
	{
		_font = font;
	}

	void TextView::setTextSize(unsigned short size)
	{
		_textSize = size;
	}

	void TextView::setText(const std::string& text)
	{
		_text = text;
	}

}