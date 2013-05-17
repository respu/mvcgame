

#ifndef mvcgame_TextView_hpp
#define mvcgame_TextView_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/view/Color.hpp>

#include <string>

namespace mvcgame {

	class TextView : public View
	{
	public:
		enum class HorizontalAlign
		{
			Left,
			Right,
			Center
		};
		enum class VerticalAlign
		{
			Top,
			Bottom,
			Center
		};

	protected:
		HorizontalAlign _textHorizAlign;
		VerticalAlign _textVertiAlign;
		std::string _text;
		Color _textColor;
		std::string _textFont;
		unsigned short _textSize;
	public:
		TextView();
		virtual void setTextHorizontalAlign(HorizontalAlign align);
		virtual void setTextVerticalAlign(VerticalAlign align);
		virtual void setTextFont(const std::string& font);
		virtual void setTextSize(unsigned short size);
		virtual void setText(const std::string& text);
		virtual void setTextColor(const Color& color);
	};

}

#endif