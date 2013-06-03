

#ifndef mvcgame_TextView_hpp
#define mvcgame_TextView_hpp

#include <mvcgame/view/View.hpp>
#include <mvcgame/base/Color.hpp>
#include <mvcgame/texture/FontAtlas.hpp>

#include <string>

namespace mvcgame {

	class TextView : public View
	{
	public:
		typedef FontAtlas Font;
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
		HorizontalAlign _horizAlign;
		VerticalAlign _vertiAlign;
		std::string _text;
		std::shared_ptr<Font> _font;
		unsigned short _textSize;
	public:
		TextView();

		void setHorizontalAlign(HorizontalAlign align);
		void setVerticalAlign(VerticalAlign align);
		void setFont(std::shared_ptr<Font> font);
		void setTextSize(unsigned short size);
		void setText(const std::string& text);
	};

}

#endif