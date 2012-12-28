

#ifndef mvcgame_ITextView_hpp
#define mvcgame_ITextView_hpp

#include <string>

namespace mvcgame {

	class Color;

	class ITextView
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

		virtual void setTextHorizontalAlign(HorizontalAlign align) = 0;
		virtual void setTextVerticalAlign(VerticalAlign align) = 0;
		virtual void setTextFont(const std::string& font) = 0;
		virtual void setTextSize(unsigned short size) = 0;
		virtual void setText(const std::string& text) = 0;
		virtual void setTextColor(const Color& color) = 0;
	};

}

#endif