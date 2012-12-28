

#include <mvcgame/view/BaseTextView.hpp>

namespace mvcgame {

	void BaseTextView::setTextHorizontalAlign(ITextView::HorizontalAlign align)
	{
		_textHorizAlign = align;
	}

	void BaseTextView::setTextVerticalAlign(ITextView::VerticalAlign align)
	{
		_textVertiAlign = align;
	}

	void BaseTextView::setTextFont(const std::string& font)
	{
		_textFont = font;
	}

	void BaseTextView::setTextSize(unsigned short size)
	{
		_textSize = size;
	}

	void BaseTextView::setText(const std::string& text)
	{
		_text = text;
	}

	void BaseTextView::setTextColor(const Color& color)
	{
		_textColor = color;
	}
}