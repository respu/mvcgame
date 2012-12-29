

#ifndef mvcgame_BaseTextView_hpp
#define mvcgame_BaseTextView_hpp

#include <mvcgame/view/ITextView.hpp>
#include <mvcgame/view/Color.hpp>

namespace mvcgame {

	class BaseTextView : public ITextView
	{
	protected:
		ITextView::HorizontalAlign _textHorizAlign;
		ITextView::VerticalAlign _textVertiAlign;
		std::string _text;
		Color _textColor = Colors::White;
		std::string _textFont;
		unsigned short _textSize;
	public:
		virtual void setTextHorizontalAlign(ITextView::HorizontalAlign align);
		virtual void setTextVerticalAlign(ITextView::VerticalAlign align);
		virtual void setTextFont(const std::string& font);
		virtual void setTextSize(unsigned short size);
		virtual void setText(const std::string& text);
		virtual void setTextColor(const Color& color);
	};

}

#endif